#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "../include/windowing.hpp"

namespace lsr::renderer {

struct Renderer {
  Display           *_display   = NULL;

  Renderer() {}

  Renderer(int disp_num) : _display(XOpenDisplay(NULL))
  {

  }

  bool Init();
  void Connect();
  };


} // NS lsr
