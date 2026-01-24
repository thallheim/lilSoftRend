#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <xcb/xcb.h>

#include "../include/windowing.hpp"

namespace lsr::renderer {

struct Renderer {
  Display* _display = NULL;
  Window*  _window  = NULL;
  Screen*  _screen  = NULL;

  Renderer(Display *d, Window *w, Screen *s)
    : _display(d), _window(w), _screen(s)
  {

  }

  bool Init();
};


} // NS lsr
