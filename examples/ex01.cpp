#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include <stdexcept>
#include <unistd.h>


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <map>
#include <unistd.h>
#include <X11/Xlib.h>

using namespace lsr::renderer;
using std::print;

int main()
{
  // Open display
  Renderer r;
  r.Connect();

  // Get some colors
  int cblack = BlackPixel(r._display, DefaultScreen(r._display));
  int cwhite = WhitePixel(r._display, DefaultScreen(r._display));

  // Create the window
  Window win = XCreateSimpleWindow(r._display, DefaultRootWindow(r._display),
                                   0, 0, 200, 100, 0, cblack, cblack);

  // Select MapNotify events
  XSelectInput(r._display, win, StructureNotifyMask);

  // Map window
  XMapWindow(r._display, win);

  // Create graphics ctx
  GC gc = XCreateGC(r._display, win, 0, NULL);

  // Tell the GC we draw using the white color
  XSetForeground(r._display, gc, cwhite);

  // Wait for the MapNotify event
  for(;;) {
    XEvent e;
    XNextEvent(r._display, &e);
    if (e.type == MapNotify)
      break;
  }

  // Draw the line
  XDrawLine(r._display, win, gc, 10, 60, 180, 20);

  // Send the "DrawLine" request to the server
  XFlush(r._display);

  // Wait
  pause();

  return 0;
}
