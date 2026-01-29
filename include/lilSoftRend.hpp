#pragma once
#include <GLFW/glfw3.h>
#include <vector>

#include "types.hpp"
#include "enums.hpp"

namespace lsr {

struct Renderer {

  std::vector<GLFWwindow *> windows;
  std::vector<FBO>          fbos;
  FBO*                      fbo_active;
  Renderer() {}

  bool init(WINDOWING_API api = WINDOWING_API::X11);
  void shutdown();

  bool setFBO(FBO *fbo);

  // Drawing
  void drawPixel(int posX, int posY, uchar r, uchar g, uchar b, uchar a = 255);


  // Window stuff
  void addWindow(int width, int height, const char *title,
                 bool dbuffered = true);
  void addWindow(GLFWwindow *window);
  GLFWwindow *getWindowById(size_t id);
};

} // NS lsr
