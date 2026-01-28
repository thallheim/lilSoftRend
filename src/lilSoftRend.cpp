#include <print>
#include "GLFW/glfw3.h"
#include "../include/lilSoftRend.hpp"
#include "../include/windowing.hpp"

bool lsr::renderer::Renderer::init() {
  if (!glfwInit()) {
    std::print(stderr,"ERROR: Failed to initialise GLFW\n");
    return false;
  }

  return true;
}

void lsr::renderer::Renderer::AddWindow(int width, int height, const char *title,
                                      bool dbuffered) {
  this->windows.emplace_back(lsr::window::CreateSimple(width, height, title, dbuffered));
}

GLFWwindow* lsr::renderer::Renderer::GetWindowById(size_t id) {
  if (!this->windows.empty() && this->windows.size() >= id) {
    return this->windows.at(id);
  }
  std::print(stderr, "ERROR: Window ID ({}) out of range\n", id);
  return nullptr;  
}
