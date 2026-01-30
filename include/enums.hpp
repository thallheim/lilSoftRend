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
namespace lsr::colours {

  enum class Base : uint32_t {
    Black = 0,
    White,
    Red,
    Green,
    Blue,
};

//   enum class Base : uint32_t {
//     Black = 0x000000,
//     White = 0xffffff,
//     Red   = 0xff0000,
//     Green = 0x00f000,
//     Blue  = 0x0000ff,
// };

  enum class Bg : uint32_t {
    Black = (uint32_t)Base::Black,
    White = (uint32_t)Base::White,
    Red   = (uint32_t)Base::Red,
    Green = (uint32_t)Base::Green,
    Blue  = (uint32_t)Base::Blue,
};

  enum class Fg : uint32_t {
    Black = (uint32_t)Base::Black,
    White = (uint32_t)Base::White,
    Red   = (uint32_t)Base::Red,
    Green = (uint32_t)Base::Green,
    Blue  = (uint32_t)Base::Blue,
};

}
