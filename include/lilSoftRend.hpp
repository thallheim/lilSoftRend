#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include "../include/windowing.hpp"

namespace lsr::renderer {

struct Renderer {
  int               _display    = NULL;
  xcb_connection_t  *_disp_conn = NULL;
  xcb_screen_t      *_screen    = NULL;
  xcb_window_t      *_window    = NULL;

  Renderer() {}

  Renderer(int disp_num, xcb_window_t *w, xcb_screen_t *s)
    : _display(disp_num), _window(w), _screen(s)
  {

  }

  bool Init();
  void Connect();
  };


} // NS lsr
