#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <print>

#include "../include/lilSoftRend.hpp"
#include "enums.hpp"
#include "types/colour.hpp"

using namespace lsr;
using std::print;

bool Renderer::Init() {
  ConnectDefaultDisplay();

  screen = XDefaultScreenOfDisplay(display);
  if (!screen) {
    print(stderr, "ERROR: Failed: Connect default screen.\n");
    return false;
  }

  return true;
}

// TODO: throw, probably
bool Renderer::ConnectDefaultDisplay() {
  display = XOpenDisplay(NULL);

  if (display) return true;
  else {
    print(stderr, "ERROR: Failed: {}.\n", __FUNCTION__);
    return false;
  }
}

Screen* Renderer::GetScreen(int scr) {
  if (!display) {
    print(stderr, "ERROR: {}: No display connected.\n", __FUNCTION__);
    // TODO: error handling?
    return NULL;
  }
  return XScreenOfDisplay(display, scr);
}

Window Renderer::CreateWindow(Display *disp, Window *parent, int px, int py,
                              uint width, uint height, uint border_width,
                              ulong border, ulong background, const char *title) {
  using namespace lsr::colour;

  if (!display) {
    print(stderr, "ERROR: {}: No display connection active.\n", __FUNCTION__);
    // TODO: error handling
  }

  GC gc = screen->default_gc;

  Window w = XCreateSimpleWindow(disp, *parent, px, py, width, height,
                                 border,
                                 NamedColour.at("black"),
                                 NamedColour.at("darkgrey"));

  if (title) XStoreName(disp, w, title); // set title if provided
  _windows_count++;
  return w;
}

Window Renderer::CreateWindow(Display *disp, Window *parent, const char *title) {
  using namespace lsr::colour;
  // TODO: un-hardcode dimensions: stuff into fields somewhere.
  // TODO: if not root, maybe grab pX & pY from parent window?
  return CreateWindow(disp, parent, 0, 0, 800, 600,
                      0, 0x000000, 0x000000, title);
}

Window Renderer::CreateWindow(Display *disp, Window *parent,
                              BaseColour bgcolour, BaseColour fgcolour,
                              const char *title) {
  // TODO: un-hardcode dimensions: stuff into fields somewhere.
  // TODO: if not root, maybe grab pX & pY from parent window?

  // if (BaseColourMap.contains(bgcolor)
  return CreateWindow(disp, parent, 0, 0, 800, 600,
                      0, 0x000000, 0x000000, title);
}

const char* Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

void Renderer::ClearError() { emsg = NULL; ekind = ErrorKind::NONE; }

Screen* Renderer::GetDefaultScreen(Display* dsp) {
  return XDefaultScreenOfDisplay(dsp);
}

Visual* Renderer::GetDefaultVisual(Screen *scr) {
  return XDefaultVisualOfScreen(scr);
}

Colormap Renderer::GetDefaultColourmap(Screen* scr) {
  return XDefaultColormapOfScreen(scr);
}
