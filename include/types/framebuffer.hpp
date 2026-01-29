#pragma once
#include <cstring>
#include <print>

using uchar = unsigned char;
using uint  = unsigned int;

namespace lsr {

  /**
   * @brief Framebuffer object.
   * Holds a drawable's pixel data.
   */
  struct FBO {
    uint width;
    uint height;
    uchar* data;

    /** Framebuffer constructor. */
    FBO(uint size_x, uint size_y) {
      width = size_x;
      height = size_y;

      data = new uchar[width*height*4]; // RGBA
      memset(data, 0, width*height*4);
    }

    /** Framebuffer destructor. */
    ~FBO() { delete[] data; }

    /** Framebuffer data setter. */
    void set(uchar *data) {
      if (!data) {
        std::print(stderr, "Warn: Can't set FBO data: Input empty.\n");
        return;
      }
      this->data = data;
    }

  }; // framebuf

}
