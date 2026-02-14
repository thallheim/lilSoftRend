#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
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

static const uint LSR_MAX_CONTEXTS {512};


namespace lsr {

  // TODO: move to renderer types subheader
  struct WinInfo {
    string name;
    string title;
    size_t widx;  // Idx into Renderer's `windows` vec

    WinInfo(const char* name, const char *title, size_t v_idx)
      : name(string(name)), title(string(title)), widx(v_idx) {}

  }; // WinInfo


struct Renderer {
  lsr::ErrorKind       ekind;
  const char           *emsg     = NULL;

  Display              *display  = NULL;
  Screen               *screen   = NULL;
  vector<WinInfo>      win_info;
  vector<Window>       windows;
  GC                   gcs[LSR_MAX_CONTEXTS] {0};
  size_t               gc_count = 0;
  map<string, size_t>  _contextIDs; // <GC name, idx>

private:
  size_t               _errors_count = 0;

  /** Connect to default X11 server/Display. */
  /// Called by `Init()`.
  bool ConnectDefaultDisplay();

public:
  Renderer() { Init(); }

  ~Renderer() {
    for (WinInfo wi : win_info) {
      XDestroyWindow(display, windows.at(wi.widx));
    }

  }

  void NewWindow(Display *disp, Window parent, int px, int py, uint width,
                    uint height, uint border_width, ulong border,
                    ulong background, const char* name,
                    const char *title = NULL);

  void NewWindow(Display *disp, Window parent, const char* name,
                    const char *title = NULL);

  void NewWindow(Display *disp, Window parento, BaseColour bgcolour,
                    BaseColour fgcolour, const char* name,
                    const char *title = NULL);

  void NewGC(const char* name, Drawable drw);

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

  GC      GetGCByName(const char* name);

  /** @brief Ptr to default Screen of Display `dsp`.
   * Returns NULL on failure.
   */
  static Screen*  GetDefaultScreen(Display* dsp);
  static Visual*  GetDefaultVisual(Screen* scr);
  static Colormap GetDefaultColourmap(Screen* scr);



  }; // Renderer


} // NS lsr
