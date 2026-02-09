#include "enums.hpp"
#include "types.hpp"
#include <lilSoftRend.hpp>
#include <print>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdexcept>

using namespace lsr;
using std::print;

bool Renderer::Init() {
  if (!ConnectDefaultDisplay()) {
    print(stderr, "ERROR: Init() failed: Couldn't connect to default Display.\n");
    return false;
  }

  screen = XDefaultScreenOfDisplay(display);
  if (!screen) {
    print(stderr, "ERROR: Failed: Connect default screen.\n");
    return false;
  }

  contexts[0] = screen->default_gc; // add default GC
  _winname2idx.emplace("default", (size_t)contexts[0]);
  win_info.emplace_back(WinInfo("default", "@default@", win_info.size()));
  ctx_count++;

  return true;
}

// TODO: throw, probably
bool Renderer::ConnectDefaultDisplay() {
  display = XOpenDisplay(NULL);
  if (display) return true;
  return false;
}

Screen* Renderer::GetScreen(int scr) {
  if (!display) {
    print(stderr, "ERROR: {}: No display connected.\n", __FUNCTION__);
    // TODO: error handling?
    return NULL;
  }
  return XScreenOfDisplay(display, scr);
}

Window Renderer::GetWindow(int w) {
  if (win_info.empty() || w > win_info.size() - 1) {
    const auto emsg = string("Bad Window ID: {}", w);
    print(stderr, "ERROR: {}: Window ID out of range ({}).\n", __FUNCTION__, w);
    std::out_of_range(emsg.c_str());
  }

  return windows.at(w);
}

void Renderer::CreateWindow(Display *disp, Window *parent, int px, int py,
                              uint width, uint height, uint border_width,
                            ulong border, ulong background, const char* name,
                            const char *title) {
  using namespace lsr::colour;

  if (!display) {
    print(stderr, "ERROR: {}: No display connection active.\n", __FUNCTION__);
    // TODO: error handling
  }



  Window w = XCreateSimpleWindow(disp, *parent, px, py, width, height,
                                 border,
                                 0x0, // border colour
                                 background);

  if (title) XStoreName(disp, w, title); // set title if provided

  win_info.emplace_back(WinInfo(name, title, win_info.size()));
  _winname2idx.emplace(name, _winname2idx.size());
  // TODO: don't throw?
  if (_winname2idx.size() != win_info.size()) {
    print(stderr, "ERROR: {}: WinInfo vec & Window idx map size mismatch ({} != {})\n", __FUNCTION__, _winname2idx.size(), win_info.size());
    throw std::runtime_error("WinInfo vec & Window idx map size mismatch");
  }
}

void Renderer::CreateWindow(Display *disp, Window *parent, const char* name,
                            const char *title) {
  CreateWindow(disp, parent, 0, 0, 800, 600, 0,
               0x0, // border colour
               GetColour(BaseColour::Black), name, title);
}

void Renderer::CreateWindow(Display *disp, Window *parent, BaseColour bgcolour,
                            BaseColour fgcolour, const char* name,
                            const char *title) {
  // TODO: un-hardcode dimensions: grab defaults from somewhere
  // TODO: if not root, maybe grab pX & pY from parent window?
  // TODO: un-hardcode border width & colour
  CreateWindow(disp, parent, 0, 0, 800, 600, 0,
               0x0, // border colour
               GetColour(bgcolour), name, title);
}

void Renderer::NewGC(const char *name, Drawable drw, Display *dsp) {
  size_t i = _contextIDs.size();
  contexts[i] = XCreateGC(dsp, drw, 0, NULL);
  _contextIDs.emplace(name, i);
}

const char* Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

void Renderer::ClearError() { emsg = NULL; ekind = ErrorKind::NONE; }

Window Renderer::GetWindowByName(const char* name) {
  for (auto wi : win_info) {
    if (wi.name == name) return windows.at(_winname2idx.at(name));
  }
  print(stderr, "ERROR: {}: No alive window named '{}'.\n", name, __FUNCTION__);
  return 0;
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
