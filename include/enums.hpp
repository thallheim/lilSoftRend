#pragma once
#include <cstdint>

namespace lsr {

/*********************************************
 * Errors
 ********************************************/
enum class ErrorKind : uint16_t {
  NONE = 0,
};

}


/*********************************************
 * Colours
 ********************************************/
namespace lsr::colour {

  enum class BaseColour : uint32_t {
    Black = 0,
    White,
    Red,
    Green,
    Blue,
};

  enum class Bg : uint32_t {
    Black = (uint32_t)BaseColour::Black,
    White = (uint32_t)BaseColour::White,
    Red   = (uint32_t)BaseColour::Red,
    Green = (uint32_t)BaseColour::Green,
    Blue  = (uint32_t)BaseColour::Blue,
};

  enum class Fg : uint32_t {
    Black = (uint32_t)BaseColour::Black,
    White = (uint32_t)BaseColour::White,
    Red   = (uint32_t)BaseColour::Red,
    Green = (uint32_t)BaseColour::Green,
    Blue  = (uint32_t)BaseColour::Blue,
};


  enum class Channel : uint8_t { a = 0, r, g, b };

} // NS colour
