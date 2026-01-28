#include <print>
#include "GLFW/glfw3.h"
#include "../include/callbacks.hpp"
#include "../include/lilSoftRend.hpp"
#include "../include/windowing.hpp"

using namespace lsr;

/**
 * @brief Initialise the renderer.
 * Also inits the GLFW platform backend (defaulting to X11 on Linux)
 * and sets an error callback.
 * @returns True on success; False otherwise.
*/
bool Renderer::init() {
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

void Renderer::AddWindow(int width, int height,
                         const char *title, bool dbuffered) {
  windows.emplace_back(window::CreateSimple(width, height, title, dbuffered));
}

GLFWwindow* Renderer::GetWindowById(size_t id) {
  if (!windows.empty() && windows.size() >= id) {
    return windows.at(id);
  }
  std::print(stderr, "ERROR: Window ID ({}) out of range\n", id);
  return nullptr;
}
