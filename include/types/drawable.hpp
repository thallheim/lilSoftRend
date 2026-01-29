#pragma once
#include <print>
#include <stdexcept>

struct Drawable2d {
  int rows, cols;
  double **data;

  /**
   * @brief Default `Drawable2d` constructor.
   * Allocates and zero-initialises internal data arrays according to params.
   * @param `r` Number of rows desired.
   * @param `c` Number of columns desired.
  */
  Drawable2d(int r, int c) : rows(r), cols(c) {
    // Allocate & zero-init
    data = new double *[rows];
    for (int i = 0; i < rows; ++i) {
      data[i] = new double[cols]();
    }
  }

  /**
   * @brief `Drawable2d` destructor.
  */
  ~Drawable2d() {
    for (int i = 0; i < rows; ++i) delete[] data[i];
    delete[] data;
  }

  /**
   * @brief Value getter.
   * Get value by index.
   * @param `row` index
   * @param `col` index
   * @return `double` on success; throws if out of range
  */
  double get(int row, int col) const {
    if (!idxinrange(row, col)) {
      throw std::out_of_range(estr_idxrange);
    }
    return data[row][col];
  }

  /**
   * @brief Value setter.
   * Set value by index.
   * @param `row` index
   * @param `col` index
   * @param New value
  */
  void set(int row, int col, double value) {
    if (!idxinrange(row, col)) {
      throw std::out_of_range(estr_idxrange);
    }
    data[row][col] = value;
  }

private:
  const char *estr_idxrange = "ERROR: Index out of range";

  bool idxinrange(int row, int col) const {
    if (!idxinrange(row, col)) {
      std::print(stderr, "{}", estr_idxrange);
      return false;
    }
    return true;
  }
}; // Drawable2d
