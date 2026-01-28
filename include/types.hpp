#pragma once

struct Drawable2d {
  int rows, cols;
  double **data;

  Drawable2d(int r, int c) : rows(r), cols(c) {
    // Allocate & zero-init
    data = new double *[rows];
    for (int i = 0; i < rows; ++i) {
      data[i] = new double[cols]();
    }
  }

  ~Drawable2d() {
    for (int i = 0; i < rows; ++i) delete[] data[i];
    delete[] data;
  }

};
