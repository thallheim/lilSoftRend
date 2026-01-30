#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "../include/windowing.hpp"

namespace lsr::renderer {

struct Renderer {
  Display *display = NULL;
  Window **windows = NULL;

  Renderer() {
    Init();
    ConnectDisplay();
  }

  Renderer(int disp_num) : display(XOpenDisplay(NULL))
  {
    Init();
  }

private:
  bool Init();
  void ConnectDisplay();
  };


} // NS lsr
