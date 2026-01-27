#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <map>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <X11/Xlib.h>


int main() {
  using namespace lsr::renderer;
  using std::print;
  using std::println;

  Renderer r;
  int disp_id;
  r._disp_conn = xcb_connect (NULL, &disp_id);

  std::map<std::string, uint32_t> ids;
  ids.emplace("window", xcb_generate_id(r._disp_conn));

  auto win = xcb_create_window(r._disp_conn, XCB_COPY_FROM_PARENT, ids.at("window"), NULL,
                    0, 0, 800, 600, 1, XCB_WINDOW_CLASS_COPY_FROM_PARENT,
                    XCB_COPY_FROM_PARENT, XCB_BACK_PIXMAP_NONE, NULL);
  xcb_map_window(r._disp_conn, win);

  xcb_disconnect(r._disp_conn);

  print("Disp: {}\n", disp_id);
  return 0;
}
