#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "../include/windowing.hpp"
#include "../include/types.hpp"
#include "../include/enums.hpp"

using uchar = unsigned char;
using uint  = unsigned int;
using ulong = unsigned long;
using std::map;

using namespace lsr::colour;

namespace lsr {

struct Renderer {
  lsr::ErrorKind  ekind;
  const char      *emsg = NULL;

  Display         *display  = NULL;
  Screen          *screen   = NULL;
  Window          **windows = NULL;
  map<string, GC> contexts;

  Renderer() { Init(); }

  ~Renderer() {
    for (int i = 0; i < sizeof(_windows_count) / sizeof(windows[0]); ++i)
      XDestroyWindow(display, *windows[i]);
    delete[] windows;
  }

  Window CreateWindow(Display *disp, Window *parent, int px, int py,
                      uint width, uint height, uint border_width,
                      ulong border, ulong background, const char *title = NULL);

  Window CreateWindow(Display *disp, Window *parent, const char *title = NULL);

  Window CreateWindow(Display *disp, Window *parent,
                      BaseColour bgcolour, BaseColour fgcolour,
                      const char *title = NULL);

  const char* GetError() const;
  void        ClearError();


  /** Initialise renderer.
   * Called by Renderer constructor.
   */
  bool Init();

  /** @brief Ptr to Screen `scr`. Returns NULL on failure. */
  Screen *GetScreen(int scr);

  /** @brief Ptr to default Screen of Display `dsp`.
   * Returns NULL on failure.
   */
  static Screen*  GetDefaultScreen(Display* dsp);
  static Visual*  GetDefaultVisual(Screen* scr);
  static Colormap GetDefaultColourmap(Screen* scr);

private:
  size_t _windows_count = 0;

  /** Connect to default X11 server/Display.
   * Called by Init().
   */
  bool ConnectDefaultDisplay();


  }; // Renderer


} // NS lsr
