#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

namespace lsr::window {

  Window* New(const char* title, int height, int width);

} // NS lsr::windowing
