#include <print>
#include "../include/lilSoftRend.hpp"

bool lsr::renderer::Renderer::Init() {

  return false;
}

void lsr::renderer::Renderer::Connect() {
  _display = XOpenDisplay(NULL);

  if (!_display) {
    std::print(stderr, "ERROR: Couldn't connect to display\n");
    throw std::runtime_error("Couldn't connect to display");
  }

}
