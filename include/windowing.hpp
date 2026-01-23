#pragma once

#include <GLFW/glfw3.h>

#include "../include/callbacks.hpp"
#include "../include/input.hpp"

namespace lsr::window {

  GLFWwindow *CreateSimple(int width, int height, const char *title,
                           bool dbuffered = GLFW_TRUE);

  GLFWwindow *CreateSimple(int width, int height, int px, int py,
                           const char *title,
                           bool dbuffered = GLFW_TRUE);

} // NS lsr::windowing
