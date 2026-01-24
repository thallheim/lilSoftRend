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

  Renderer r;

  double start;

  xcb_connection_t *connection = xcb_connect (NULL, NULL);


  return 0;
}
