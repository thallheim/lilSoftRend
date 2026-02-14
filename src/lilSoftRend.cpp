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

  // TODO: necessary? if yes; account for it
  gcs[0] = screen->default_gc; // add default GC
  gc_count++;

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
  if (win_info.empty() || w > win_info.size()) {
    const auto emsg = string("Bad Window ID: {}", w);
    print(stderr, "ERROR: {}: Window ID out of range ({}).\n", __FUNCTION__, w);
    throw std::out_of_range(emsg.c_str());
  }

  return windows.at(w);
}

void Renderer::NewWindow(Display *disp, Window parent, int px, int py,
                              uint width, uint height, uint border_width,
                            ulong border, ulong background, const char* name,
                            const char *title) {
  using namespace lsr::colour;

  if (!display) {
    print(stderr, "ERROR: {}: No display connection active.\n", __FUNCTION__);
    // TODO: error handling
  }

  Window w = XCreateSimpleWindow(disp, parent, px, py, width, height,
                                 border,
                                 0x0, // border colour
                                 background);

  if (title) XStoreName(disp, w, title); // set title if provided

  win_info.emplace_back(WinInfo(name, title, win_info.size()));
  windows.emplace_back(w);

  if (windows.size() != win_info.size()) {
    print(stderr,
          "FATAL: {}(): Vector size mismatch: WinInfo ({}) != Windows ({})\n",
          __FUNCTION__, windows.size(), win_info.size());
    throw std::runtime_error("WinInfo vec & Window vec size mismatch");
  }
}

void Renderer::NewWindow(Display *disp, Window parent, const char* name,
                            const char *title) {
  NewWindow(disp, parent, 0, 0, 800, 600, 0,
               0x0, // border colour
               GetColour(BaseColour::Black), name, title);
}

void Renderer::NewWindow(Display *disp, Window parent, BaseColour bgcolour,
                            BaseColour fgcolour, const char* name,
                            const char *title) {
  // TODO: un-hardcode dimensions: grab defaults from somewhere
  // TODO: if not root, maybe grab pX & pY from parent window?
  // TODO: un-hardcode border width & colour
  NewWindow(disp, parent, 0, 0, 800, 600, 0,
               0x0, // border colour
               GetColour(bgcolour), name, title);
}

void Renderer::NewGC(const char *name, Drawable drw) {
  size_t i = _contextIDs.size();
  GC gc = XCreateGC(display, drw, 0, NULL);
  gcs[i] = gc;
  _contextIDs.emplace(name, i);
  gc_count++;
}

const char* Renderer::GetError() const {
  if (!emsg) return NULL;
  return emsg;
}

void Renderer::ClearError() { emsg = NULL; ekind = ErrorKind::NONE; }

Window Renderer::GetWindowByName(const char* name) {
  for (auto wi : win_info) {
    if (wi.name == name) return windows.at(wi.widx);
  }
  print(stderr, "ERROR: {}: No alive window named '{}'.\n", name, __FUNCTION__);
  return 0;
}

GC Renderer::GetGCByName(const char *name) {
  if (!_contextIDs.contains(name)) {
    print(stderr, "ERROR: {}: GC '{}' doesn't exist.\n", name, __FUNCTION__);
    return NULL;
  }
  size_t i = _contextIDs.at(name);
  return gcs[i];
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
