#include <print>
#include "GLFW/glfw3.h"
#include "../include/callbacks.hpp"
#include "../include/lilSoftRend.hpp"
#include "../include/windowing.hpp"
#include "types/framebuffer.hpp"

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
    glfwTerminate();
    return false;
  }

  return true;
}

void Renderer::shutdown() {
  for (auto *w : windows) {
    glfwDestroyWindow(w);
  }
  glfwTerminate();
}

bool Renderer::setFBO(FBO *fb) {
  if (fbo_active) fbo_active = nullptr; // release current FBO, if set
  if (!fb) {
    std::print(stderr, "Error: Can't set active FBO: Invalid framebuffer pointer.\n");
    return false;
  }
  fbo_active = fb;
  return true;
}

/** @brief Draw a pixel into active #FBO.
 * RGBA - values accepted 0-255.
 */
void Renderer::drawPixel(int posX, int posY, uchar r, uchar g, uchar b, uchar a) {
  if (!fbo_active) { // no FBO active
    std::print(stderr,
               "Error: Renderer: Can't draw pixel(s) with no FBO active.");
    return;
  }

  if (posX < 0 || posX > fbo_active->width ||
      posY < 0 || posY > fbo_active->height) return; // boundary check
  int pidx = (posX * fbo_active->width * posY) * 4; // pixel index
  this->fbo_active->data[pidx + 0] = r;
  this->fbo_active->data[pidx + 1] = g;
  this->fbo_active->data[pidx + 2] = b;
  this->fbo_active->data[pidx + 3] = a;
}

void Renderer::addWindow(int width, int height,
                         const char *title, bool dbuffered) {
  windows.emplace_back(window::CreateSimple(width, height, title, dbuffered));
}

void Renderer::addWindow(GLFWwindow *window) {
  windows.emplace_back(window);
}

GLFWwindow* Renderer::getWindowById(size_t id) {
  if (!windows.empty() && windows.size() >= id) {
    return windows.at(id);
  }
  std::print(stderr, "ERROR: Window ID ({}) out of range\n", id);
  return nullptr;
}
