#pragma once

namespace lsr {

  /**
   * @brief Simple 2d float container
   */
  struct vec2f {
    float x;
    float y;

    vec2f(float x, float y) {
      this->x = x;
      this->y = y;
    }

    void set(float x, float y) {
      this->x = x;
      this->y = y;
    }

  }; // vec2f


  /**
   * @brief Simple 3d float container
   */
  struct vec3f {
    float x;
    float y;
    float z;

    vec3f(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    void set(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

  }; // vec3f


  /**
   * @brief Simple 4d float container
   */
  struct vec4f {
    float x;
    float y;
    float z;
    float w;

    vec4f(float x, float y, float z, float w) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }

    void set(float x, float y, float z, float w) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }

  }; // vec4f

}
