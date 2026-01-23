#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include "GLFW/glfw3.h"


#define W_WIDTH 800
#define W_HEIGHT 600

int main() {
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow* window = lsr::window::CreateSimple(W_WIDTH, W_HEIGHT, "Window example");

  if (!window) {
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // do rendering things here
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
