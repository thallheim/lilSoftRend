#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <print>
#include "../include/lilSoftRend.hpp"
#include "enums.hpp"

using namespace lsr;
using std::print;

bool Renderer::Init() {
  ConnectX11Server();

  default_screen = XDefaultScreenOfDisplay(display);
  if (!default_screen) {
    print(stderr, "ERROR: Failed: Query default screen.\n");
    return false;
  }

  return true;
}

Window Renderer::CreateWindow(Display *disp, Window *parent, int px, int py,
                              uint width, uint height, uint border_width,
                              ulong border, ulong background, const char *title) {
  if (!display) {
    print(stderr, "ERROR: {}: No display connection active.\n", __FUNCTION__);
    // TODO: error handling
  }

  int cblack = BlackPixel(disp, DefaultScreen(disp));
  int cwhite = WhitePixel(disp, DefaultScreen(disp));
  Screen *scr = XScreenOfDisplay(disp, 0);
  GC gc = scr->default_gc;

  Window w = XCreateSimpleWindow(disp, *parent, px, py, width, height,
                                 border, cblack, cblack);

  if (title) XStoreName(disp, w, title); // set title if provided
  return w;
}

Window Renderer::CreateWindow(Display *disp, Window *parent, const char *title) {
  // TODO: un-hardcode dimensions: stuff into fields somewhere.
  // TODO: if not root, maybe grab pX & pY from parent window?
  return CreateWindow(disp, parent, 0, 0, 800, 600,
                      0, 0x000000, 0x000000, title);
}

const char* Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

void Renderer::ClearError() { emsg = NULL; ekind = ErrorKind::NONE; }

// TODO: don't throw
void Renderer::ConnectX11Server(const char *disp_name) {
  display = XOpenDisplay(disp_name);

  if (!display) {
    print(stderr, "ERROR: Couldn't connect to display\n");
    throw std::runtime_error("Couldn't connect to display");
  }
}

Screen* Renderer::GetDefaultScreen(Display* dsp) {
  return XDefaultScreenOfDisplay(dsp);
}

Visual* Renderer::GetDefaultVisual(Screen *scr) {
  return XDefaultVisualOfScreen(scr);
}

Colormap Renderer::GetDefaultColourmap(Screen* scr) {
  return XDefaultColormapOfScreen(scr);
}
