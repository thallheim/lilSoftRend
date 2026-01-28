#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include "GLFW/glfw3.h"

using namespace lsr;

#define W_WIDTH  800
#define W_HEIGHT 600

int main() {
  Renderer r;
  if (!r.init()) return -1;

  r.AddWindow(W_WIDTH, W_HEIGHT, "Window example");

  if (!r.GetWindowById(0)) {
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(r.GetWindowById(0))) {
    glfwPollEvents();

    // do rendering things here
    // glfwSwapBuffers(r.GetWindowById(0));
  }

  r.shutdown();
  return 0;
}
