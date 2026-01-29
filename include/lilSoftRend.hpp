#pragma once
#include <GLFW/glfw3.h>
#include <vector>

#include "types.hpp"

namespace lsr {

struct Renderer {

  std::vector<GLFWwindow *> windows;
  std::vector<framebuf>     fbos;
  framebuf*                 fbo_active;
  Renderer() {}

  bool init();
  void shutdown();

  bool setFBO(framebuf *fb);

  // Drawing
  void drawPixel(int posX, int posY, uchar r, uchar g, uchar b, uchar a = 255);


  // Window stuff
  void addWindow(int width, int height, const char *title,
                 bool dbuffered = true);
  void addWindow(GLFWwindow *window);
  GLFWwindow *getWindowById(size_t id);
};

} // NS lsr
