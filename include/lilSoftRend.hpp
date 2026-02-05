#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>

#include "../include/windowing.hpp"
#include "../include/types.hpp"
#include "../include/enums.hpp"

using uchar = unsigned char;
using uint  = unsigned int;
using ulong = unsigned long;
using std::map;
using std::unordered_map;
using std::vector;

using namespace lsr::colour;

// TODO: probably shouldn't be #define. also: where to stick it?
#define LSR_MAX_CONTEXTS 256


namespace lsr {

struct WinInfo {
  string       name;
  const char*  title = NULL;
  size_t       v_idx; // Window's index in `windows` vector
  // Window       _data = NULL;

  // WinInfo(string &name, const char *title, size_t v_idx, Window w)
  //   : name(name), title(title), v_idx(v_idx), _data(w) {}

  WinInfo(string &name, const char *title, size_t v_idx)
    : name(name), title(title), v_idx(v_idx) {}

};


struct Renderer {
  lsr::ErrorKind       ekind;
  const char           *emsg     = NULL;
  Display              *display  = NULL;
  Screen               *screen   = NULL;
  vector<WinInfo>      win_info;
  vector<Window>       windows;
  GC                   contexts[LSR_MAX_CONTEXTS] {0};
  unordered_map<string, size_t> _winname_to_idx; // TODO: REMOVE - use WinInfo

private:
  size_t                        _errors_count = 0;
  map<size_t, string>           _contextIDs; // <GC store idx, GC name>

  /** Connect to default X11 server/Display.
   * Called by Init().
   */
  bool ConnectDefaultDisplay();

public:
  Renderer() { Init(); }

  ~Renderer() {
    for (WinInfo wi : win_info) {
      XDestroyWindow(display, windows.at(wi.v_idx));
    }

  }

  void CreateWindow(Display *disp, Window *parent, int px, int py, uint width,
                    uint height, uint border_width, ulong border,
                    ulong background, string &name,
                    const char *title = NULL);

  void CreateWindow(Display *disp, Window *parent, string &name,
                    const char *title = NULL);

  void CreateWindow(Display *disp, Window *parent, BaseColour bgcolour,
                    BaseColour fgcolour, string &name,
                    const char *title = NULL);

  const char* GetError() const;
  void        ClearError();


  /** Initialise renderer.
   * Called by Renderer constructor.
   */
  bool Init();

  /** @brief Ptr to Screen `scr`. Returns NULL on failure. */
  Screen* GetScreen(int scr);

  Window  GetWindow(int w);
  Window  GetWindowByName(const char* name);

  /** @brief Ptr to default Screen of Display `dsp`.
   * Returns NULL on failure.
   */
  static Screen*  GetDefaultScreen(Display* dsp);
  static Visual*  GetDefaultVisual(Screen* scr);
  static Colormap GetDefaultColourmap(Screen* scr);



  }; // Renderer


} // NS lsr
