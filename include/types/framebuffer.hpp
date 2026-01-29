#pragma once
#include <cstring>

namespace lsr {

  /**
   * @brief Framebuffer.
   * Holds a drawable's pixel data. Analogous to OpenGL's `FBO`s.
   */
  struct framebuf {
    int width  = 800;
    int height = 600;
    unsigned char* data;

    /** Framebuffer constructor */
    framebuf(int size_x, int size_y) {
      width = size_x;
      height = size_y;

      data = new unsigned char[width*height*4]; // RGBA
      memset(&data, 0, width*height*4);
    }

    /** Framebuffer destructor */
    ~framebuf() {
      delete[] data;
    }

  }; // framebuf

}
