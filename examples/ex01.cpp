#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include "GLFW/glfw3.h"
#include "types.hpp"
#include "types/vector.hpp"

using namespace lsr;

#define W_WIDTH  800
#define W_HEIGHT 600

int main() {
  Renderer r;
  if (!r.init()) return -1;
  Drawable2d d(50, 50);
  framebuf f(800, 600);
  r.setFBO(&f);
  vec3f v(1.0, 2.0, 3.6925);

  // std::print("vx: {:+.5f} vy: {:+.5f} vz: {:+.5f}\n", v.x, v.y, v.z);
  std::print("Yez\n");
  r.shutdown();
  return 0;

  r.addWindow(W_WIDTH, W_HEIGHT, "Window example");

  if (!r.getWindowById(0)) {
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(r.getWindowById(0))) {
    glfwPollEvents();

    // do rendering things here
    // glfwSwapBuffers(r.GetWindowById(0));
  }

  r.shutdown();
  return 0;
}
