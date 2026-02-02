#pragma once
#include <X11/X.h>
#include <X11/Xlib.h>
#include <algorithm>
#include <cstdint>
#include <map>
#include <stdexcept>
#include "../enums.hpp"

using namespace lsr;

using uchar = unsigned char;
using ulong = unsigned long;
using uint  = unsigned int;
using std::clamp;

struct Colour {
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t a;

  /** @brief Default `Colour` constructor.
   *
   * Accepted range [0-255]. Scaling/formatting:
   * scaleUp()/scaleDown() can be used for
   * individual values, or the AsXColor() ctor if the colour is to be
   * passed as such.
   */
  Colour(uint16_t r, uint16_t g, uint16_t b, uint16_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  /** Get colour value of channel `c`. */
  uint16_t Get(colour::Channel c) {
    using namespace colour;
    switch (c) {
    case Channel::r: return r;
    case Channel::g: return g;
    case Channel::b: return b;
    case Channel::a: return a;
    default:
      throw std::out_of_range("This was supposed to be unreachable, y'know.");
    }
  }

  XColor AsXColor() {
    XColor xcol;
    xcol.red   = scaleUp(r);
    xcol.green = scaleUp(g);
    xcol.blue  = scaleUp(b);
    xcol.flags = DoRed | DoGreen | DoBlue;

    return xcol;
  }

  /* STATICS ************************** */

  /// Scale up a [0-255] value to match X11's [0-65535] range.
  static uint16_t scaleUp(uint16_t og_value) {
    if (og_value > 255) return 0; // TODO: print error msg if og > 255
    return static_cast<uint16_t>(og_value) * (65535/255);
  }

  /// Scale down a [0-65535] value to match renderer's [0-255] range.
  static uint16_t scaleDown(uint16_t og_value) {
    return static_cast<uint16_t>(og_value) / (65535/255);
  }

}; // Colour

namespace lsr::colour {

  /** @brief Returns brightness/intensity-adjusted `Colour`.
   * To darken by 50%, pass _0.5f_, to lighten by 25%, pass _1.25f_,
   * and so on.
   * @param Source/reference #Colour.
   * @param Adjustment factor.
   */
  // TODO: ctor accepting normalised factor ([0-1])
  inline Colour brightnessAdjusted(const Colour &c, float factor) {
    return {
      static_cast<uint16_t>(clamp(c.r * factor, 0.0f, (float)c.a)),
      static_cast<uint16_t>(clamp(c.g * factor, 0.0f, (float)c.a)),
      static_cast<uint16_t>(clamp(c.b * factor, 0.0f, (float)c.a)),
      static_cast<uint16_t>(c.a)
    };
  }

  inline const std::map<std::string_view, ulong> BaseColourMap {
    {"red",   ((255 << 16) | (0 << 8) | 0) }, // 0xFF0000
    {"green", ((0 << 16) | (255 << 8) | 0) }, // 0x00FF00
    {"blue",  ((0 << 16) | (0 << 8) | 255) }, // 0x0000FF

    {"darkgrey",  (80 << 16) | (80 << 8) | 80 },
  };


} // NS colour
