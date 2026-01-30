#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "../include/windowing.hpp"
#include "../include/enums.hpp"

namespace lsr::renderer {

struct Renderer {
  lsr::ErrorKind  kind;
  const char      *emsg = NULL;


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

  Window CreateWindow(Display *disp, Window parent);

  const char* GetError() const;

private:
  bool Init();
  void ConnectDisplay(const char *display = NULL);
  };


} // NS lsr
