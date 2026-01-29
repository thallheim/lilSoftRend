#pragma once

namespace lsr {

/**
 * @brief Framebuffer.
 * Hold a drawable's pixel data. Analogous to OpenGL's `FBO`s.
 */
struct framebuf {
  static const int width  = 800;
  static const int height = 600;
  unsigned char    data[width * height * 4] = {0}; // RGBA


}; // framebuf

}
