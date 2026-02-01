#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <print>

#include "../include/lilSoftRend.hpp"
#include "enums.hpp"

using namespace lsr;
using std::print;

bool Renderer::Init() {
  ConnectX11Server();

  screen = XDefaultScreenOfDisplay(display);
  if (!screen) {
    print(stderr, "ERROR: Failed: Connect default screen.\n");
    return false;
  }

  return true;
}

// TODO: throw, probably
bool Renderer::ConnectX11Server(const char *dsp) {
  if (!dsp) display = XOpenDisplay(NULL); // use default
  if (dsp)  display = XOpenDisplay(dsp);  // use provided

  if (display) return true;
  else {
    print(stderr, "ERROR: Failed: Connect to display.\n");
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

Screen* Renderer::GetDefaultScreen(Display* dsp) {
  return XDefaultScreenOfDisplay(dsp);
}

Visual* Renderer::GetDefaultVisual(Screen *scr) {
  return XDefaultVisualOfScreen(scr);
}

Colormap Renderer::GetDefaultColourmap(Screen* scr) {
  return XDefaultColormapOfScreen(scr);
}
