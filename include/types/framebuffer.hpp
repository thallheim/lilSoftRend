#pragma once
#include <cstring>

using uchar = unsigned char;
using uint  = unsigned int;

namespace lsr {

  /**
   * @brief Framebuffer.
   * Holds a drawable's pixel data. Analogous to OpenGL's `FBO`s.
   */
  struct FBO {
    uint width;
    uint height;
    uchar* data;

    /** Framebuffer constructor */
    FBO(uint size_x, uint size_y) {
      width = size_x;
      height = size_y;

      data = new uchar[width*height*4]; // RGBA
      memset(data, 0, width*height*4);
    }

    /** Framebuffer destructor */
    ~FBO() {
      delete[] data;
    }

  }; // framebuf

}
