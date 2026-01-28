#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include "GLFW/glfw3.h"

using namespace lsr;

#define W_WIDTH 800
#define W_HEIGHT 600

int main() {
  Renderer r;
  r.init();

  // GLFWwindow* window = lsr::window::CreateSimple(W_WIDTH, W_HEIGHT, "Window example");
  r.AddWindow(W_WIDTH, W_HEIGHT, "Window example");

  if (!r.GetWindowById(0)) {
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(r.windows.back())) {
    glfwPollEvents();

    // do rendering things here
    glfwSwapBuffers(r.windows.back());
  }

  glfwDestroyWindow(r.windows.back());
  glfwTerminate();
  return 0;
}
