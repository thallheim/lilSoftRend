#include <print>
#include "../include/lilSoftRend.hpp"

bool lsr::renderer::Renderer::Init() {
  ConnectDisplay();
  return false;
}

Window lsr::renderer::Renderer::CreateWindow(Display *disp, Window parent) {
  Window w = 0;

  return w;
}

const char* lsr::renderer::Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

// TODO: don't throw
void lsr::renderer::Renderer::ConnectDisplay(const char *disp_name) {
  display = XOpenDisplay(disp_name);

  if (!display) {
    std::print(stderr, "ERROR: Couldn't connect to display\n");
    throw std::runtime_error("Couldn't connect to display");
  }

}
