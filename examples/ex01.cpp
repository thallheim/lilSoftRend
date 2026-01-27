#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include <unistd.h>


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <map>
#include <unistd.h>
#include <assert.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <X11/Xlib.h>


enum class IdType {
  DISPLAY = 0,
  WINDOW,
  GCTX,
};

#define NIL (0)       // A name for the void pointer

int main()
{
  // Open display
  Display *dpy = XOpenDisplay(NIL);
  assert(dpy);

  // Get some colors
  int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
  int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

  // Create the window
  Window win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0,
                                 200, 100, 0, blackColor, blackColor);

  // Select MapNotify events
  XSelectInput(dpy, win, StructureNotifyMask);

  // Map window
  XMapWindow(dpy, win);

  // Create graphics ctx
  GC gc = XCreateGC(dpy, win, 0, NIL);

  // Tell the GC we draw using the white color
  XSetForeground(dpy, gc, whiteColor);

  // Wait for the MapNotify event
  for(;;) {
    XEvent e;
    XNextEvent(dpy, &e);
    if (e.type == MapNotify)
      break;
  }

  // Draw the line
  XDrawLine(dpy, win, gc, 10, 60, 180, 20);

  // Send the "DrawLine" request to the server
  XFlush(dpy);

  // Wait
  pause();

  return 0;
}


int main2() {
  using namespace lsr::renderer;
  using std::print;
  using std::println;

  Renderer r;
  int disp_id;
  std::map<std::uint32_t, IdType> ids;

  r._disp_conn   = xcb_connect(NULL, &disp_id);
  r._screen      = xcb_setup_roots_iterator(xcb_get_setup(r._disp_conn)).data;
  xcb_drawable_t win = r._screen->root;
  xcb_gcontext_t ctx_black = xcb_generate_id(r._disp_conn);
  uint32_t mask = XCB_GC_FOREGROUND;
  uint32_t values[] = { r._screen->black_pixel };

  xcb_create_gc(r._disp_conn, ctx_black, win, mask, values);

  // ids.emplace("window", win);

  xcb_create_window(r._disp_conn,
                    XCB_COPY_FROM_PARENT,
                    // ids.at("window"),
                    win,
                    r._screen->root,
                    0, 0, 800, 600,
                    10,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                    r._screen->root_visual,
                    XCB_BACK_PIXMAP_NONE,
                    NULL);

  xcb_map_window(r._disp_conn, win);
  xcb_flush(r._disp_conn);
  pause();
  xcb_disconnect(r._disp_conn);

  print("Disp: {}\n", disp_id);
  return 0;
}
