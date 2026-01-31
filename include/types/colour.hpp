#pragma once
#include <cstdint>
#include <stdexcept>
#include "../enums.hpp"

using namespace lsr;

using uchar = unsigned char;
using ulong = unsigned long;
using uint  = unsigned int;

struct Colour {
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t a;

  uint16_t Get(colour::Channel c) {
    switch (c) {
    case colour::Channel::r: return r;
    case colour::Channel::g: return g;
    case colour::Channel::b: return b;
    case colour::Channel::a: return a;
    default:
      throw std::out_of_range("This was supposed to be unreachable, y'know.");
    }
  }

  /// Scale up a [0-255] value to match X11's [0-65535] range.
  static uint16_t scaleUp(uint16_t og_value) {
    if (og_value > 255) return 0; // TODO: print error msg if og > 255
    return static_cast<uint16_t>(og_value) * (65535/255);
  }

  /// Scale down a [0-65535] value to match renderer's [0-255] range.
  static uint16_t scaleDown(uint16_t og_value) {
    return static_cast<uint16_t>(og_value) / (65535/255);
  }

};
