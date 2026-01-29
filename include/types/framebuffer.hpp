#pragma once
#include <cstring>

using uchar = unsigned char;

namespace lsr {

  /**
   * @brief Framebuffer.
   * Holds a drawable's pixel data. Analogous to OpenGL's `FBO`s.
   */
  struct framebuf {
    int width;
    int height;
    uchar* data;

    /** Framebuffer constructor */
    framebuf(int size_x, int size_y) {
      width = size_x;
      height = size_y;

      data = new uchar[width*height*4]; // RGBA
      memset(data, 0, width*height*4);
    }

    /** Framebuffer destructor */
    ~framebuf() {
      delete[] data;
    }

  }; // framebuf

}
