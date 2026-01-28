#include "../include/windowing.hpp"
#include <GLFW/glfw3.h>

GLFWwindow *lsr::window::CreateSimple(int width, int height, const char *title,
                                      bool dbuffered) {
  glfwWindowHint(GLFW_DOUBLEBUFFER, dbuffered);
  return glfwCreateWindow(width, height, title, NULL, NULL);
}

GLFWwindow *CreateSimple(int width, int height, int px, int py,
                         const char *title, bool dbuffered) {
  glfwWindowHint(GLFW_DOUBLEBUFFER, dbuffered);
  glfwWindowHint(GLFW_POSITION_X, px);
  glfwWindowHint(GLFW_POSITION_Y, py);
  return glfwCreateWindow(width, height, title, NULL, NULL);
}
