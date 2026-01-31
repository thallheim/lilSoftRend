#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "../include/windowing.hpp"
#include "../include/enums.hpp"

using uchar = unsigned char;
using uint  = unsigned int;
using ulong = unsigned long;

namespace lsr {

struct Renderer {
  lsr::ErrorKind  ekind;
  const char      *emsg = NULL;

  Display *display = NULL;
  Screen* default_screen = NULL;
  Window **windows = NULL;

  Renderer() {
    Init();
    ConnectX11Server();
  }

  Renderer(int disp_num) : display(XOpenDisplay(NULL)) { Init(); }

  ~Renderer() {
    for (int i = 0; i < sizeof(windows); ++i) delete[] windows[i];
    delete[] windows;
  }

  Window CreateWindow(Display *disp, Window *parent, int px, int py,
                      uint width, uint height, uint border_width,
                      ulong border, ulong background, const char *title = NULL);
  Window CreateWindow(Display *disp, Window *parent, const char *title = NULL);

  const char* GetError() const;
  void        ClearError();

private:
  bool Init();
  void ConnectX11Server(const char *display = NULL);
  static Screen*  GetDefaultScreen(Display* dsp);
  static Visual*  GetVisual(Window* win);
  static Colormap GetColourmap(Window* win);

}; // Renderer


} // NS lsr
