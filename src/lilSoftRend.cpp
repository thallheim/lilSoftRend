#include <print>
#include "GLFW/glfw3.h"
#include "../include/callbacks.hpp"
#include "../include/lilSoftRend.hpp"
#include "../include/windowing.hpp"

/**
 * @brief Initialise the renderer.
 * Also inits the GLFW platform backend (defaulting to X11 on Linux)
 * and sets an error callback.
 * @returns True on success; False otherwise.
*/
bool lsr::Renderer::init() {
  glfwSetErrorCallback(glfwInitErrorCallback);

  if (glfwPlatformSupported(GLFW_PLATFORM_X11))
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  if (!glfwInit()) {
    const char *edesc;
    glfwGetError(&edesc);
    std::print(stderr, "{}\n", edesc);
    return false;
  }

  return true;
}

void lsr::Renderer::AddWindow(int width, int height, const char *title,
                                      bool dbuffered) {
  this->windows.emplace_back(lsr::window::CreateSimple(width, height, title, dbuffered));
}

GLFWwindow* lsr::Renderer::GetWindowById(size_t id) {
  if (!this->windows.empty() && this->windows.size() >= id) {
    return this->windows.at(id);
  }
  std::print(stderr, "ERROR: Window ID ({}) out of range\n", id);
  return nullptr;
}
