#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"

#define W_WIDTH 800
#define W_HEIGHT 600

int main() {
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "I am window example", NULL, NULL);
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
