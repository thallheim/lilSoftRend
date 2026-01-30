#include <X11/Xlib.h>
#include <print>
#include "../include/lilSoftRend.hpp"

using namespace lsr;
using std::print;

bool Renderer::Init() {
  ConnectDisplay();
  return false;
}

Window Renderer::CreateWindow(Display *disp, Window parent, const char *title) {
  if (!display) {
    print(stderr, "ERROR: {}: No display connection active.\n", __FUNCTION__);
    // TODO: error handling
  }

  Window w = 0;

  if (title) XStoreName(disp, w, title); // set title if provided

  return w;
}

const char* Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

// TODO: don't throw
void Renderer::ConnectDisplay(const char *disp_name) {
  display = XOpenDisplay(disp_name);

  if (!display) {
    print(stderr, "ERROR: Couldn't connect to display\n");
    throw std::runtime_error("Couldn't connect to display");
  }

}
