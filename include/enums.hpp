#pragma once
#include <cstdint>

namespace lsr {

/*********************************************
 * Errors
 ********************************************/
  enum class ErrorKind : uint16_t {
    NONE = 0,
  };

} // NS lsr


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
  DarkGrey,
};

  // FIXME: why 8? should've been size_t
  enum class Channel : uint8_t { a = 0, r, g, b };

} // NS colour
