#pragma once
#include <GLFW/glfw3.h>
#include <vector>

#include "callbacks.hpp"
#include "input.hpp"
#include "windowing.hpp"

namespace lsr {

struct Renderer {

  std::vector<GLFWwindow*> windows;

  Renderer() {}

  bool init();
  void shutdown();

  void AddWindow(int width, int height, const char *title,
                 bool dbuffered = true);
  void AddWindow(GLFWwindow *window);
  GLFWwindow *GetWindowById(size_t id);
};

} // NS lsr
