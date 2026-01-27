#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include <unistd.h>


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <map>
#include <unordered_set>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <X11/Xlib.h>


enum class IdType {
  DISPLAY = 0,
  WINDOW,
  GCTX,
};

void NewID(IdType kind) {
  switch (kind) {
  case IdType::DISPLAY:
  case IdType::WINDOW:
  case IdType::GCTX:
    break;
  }
}

int main() {
  using namespace lsr::renderer;
  using std::print;
  using std::println;

  Renderer r;
  int disp_id;
  std::map<std::uint32_t, IdType> ids;

  r._disp_conn = xcb_connect (NULL, &disp_id);
  xcb_window_t win = xcb_generate_id(r._disp_conn);

  const xcb_setup_t     *setup  = xcb_get_setup(r._disp_conn);
  xcb_screen_iterator_t siter   = xcb_setup_roots_iterator(setup);
  xcb_screen_t          *screen = siter.data;

  ids.emplace("window", win);

  xcb_create_window(r._disp_conn,
                    XCB_COPY_FROM_PARENT,
                    // ids.at("window"),
                    win,
                    screen->root,
                    0, 0, 800, 600,
                    10,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                    screen->root_visual,
                    XCB_BACK_PIXMAP_NONE,
                    NULL);

  xcb_map_window(r._disp_conn, win);
  xcb_flush(r._disp_conn);
  pause();
  xcb_disconnect(r._disp_conn);

  print("Disp: {}\n", disp_id);
  return 0;
}
