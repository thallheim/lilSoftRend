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

  xcb_disconnect(r._disp_conn);

  print("Disp: {}\n", disp_id);
  return 0;
}
