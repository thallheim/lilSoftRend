#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <xcb/xcb.h>
#include <X11/Xlib.h>


int main() {
  using namespace lsr::renderer;
  using std::print;
  using std::println;

  // xcb_connection_t *connection = xcb_connect (NULL, NULL);
  Renderer r;
  int d;
  r._disp_conn = xcb_connect (NULL, &d);

  // xcb_disconnect(connection);
  xcb_disconnect(r._disp_conn);
  print("Disp: {}\n", d);
  return 0;
}
