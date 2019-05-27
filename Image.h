//============================================================================
// Author      : Franck Nassé - May 27, 2019
// Version     : v1.0
// Copyright   : Copyright (c) 2019, Franck Nassé. All rights reserved.
// Description : Image class
//============================================================================
#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <cstring>

/**
 * @class Image
 * @author Franck Nassé
 * @date 27/05/2019
 * @file main.cpp
 * @brief Image structure to be retrieved and used by the media player
 * the data must be organized by column in memory 
 * Example: Image (3,4)
 * 1 2 3 4
 * 5 6 7 8
 * 0 2 6 8
 * data [1,5,0;5,6,2;3,7,6;7,8,8]
 * The main purpose of this class is to flip horizontally a frame in order mirror the current movie.
 */
class Image {
  std::size_t height_;
  std::size_t width_;
  std::vector<uint8_t*> data; // column major, array of columns

public:
 
  /**
   * @brief Constructor, creates a black image by default and initializes the main properties
   * @param nb_rows
   * @param nb_cols
   * @return 
   */
  Image(std::size_t nb_rows, std::size_t nb_cols)
      : height_(nb_rows), width_(nb_cols) {
    data.resize(nb_cols);
    for(auto it = data.begin(); it != data.end(); it++) {
      *it = new uint8_t[nb_rows]();
    }
  }
  
  /**
   * @brief Constructor which loads an image from a buffer organized in a column-by-column fashion
   * WARNING this method is not safe, caller must ensure that buffer is properly allocated
   * @param nb_rows
   * @param nb_cols
   * @param buffer  image data buffer organized in a column-by-column fashion, 
   *  buffer size must be nb_rows * nb_cols. 
   */
  Image(std::size_t nb_rows, std::size_t nb_cols, uint8_t * buffer)
      : height_(nb_rows), width_(nb_cols) {
    data.resize(nb_cols);
    std::size_t col = 0;
    assert(buffer != nullptr);
    for(auto it = data.begin(); it != data.end(); it++) {
      *it = new uint8_t[nb_rows]();
      std::memcpy(*it, buffer + nb_rows * col++, nb_rows);
    }
  }

  /**
   * @brief 
   * @return number of columns
   */
  std::size_t NumCols() const {
    return width_;
  }
  
  /**
   * @brief 
   * @return number of rows
   */
  std::size_t NumRows() const {
    return height_;
  }

  /**
   * @brief destructor
   */
  ~Image() {
    auto it = data.begin();
    for(; it != data.end(); it++) {
      delete[] * it;
    }
    width_ = 0;
    height_ = 0;
  }

  void Print() const {
    for(std::size_t i = 0; i < height_; i++) {
      for(std::size_t j = 0; j < width_; j++) {
        std::cout << (int)data[j][i] << " ";
      }
      std::cout << std::endl;
    }
  }

  // x row, y col
  void Set(std::size_t x, std::size_t y, uint8_t pix_value) {
    assert(x<height_ && y< width_);
    data[y][x] = pix_value;
  }

  // x row, y col
  uint8_t Get(std::size_t x, std::size_t y) const {
    assert(x<height_ && y< width_);
    return data[y][x];
  }

  /**
   * @brief Flips the image horizontally by swapping the columns
   */
  void MirrorFrameInPlace() {
    std::size_t x = 0, n = width_ - 1;
    while(n > x) {
      std::swap(data[n--], data[x++]);
    }
  }

  /**
   * @brief Flips the image by reversing each row
   */
  void MirrorFrameLineInPlace() {
    std::size_t n, x;
    for(std::size_t i = 0; i < height_; i++) {
      n = width_ - 1;
      x = 0;
      while(n > x) {
        std::swap(data[n--][i], data[x++][i]);
      }
    }
  }

  // x row, y col
  uint8_t GetMirrored(std::size_t x, std::size_t y) const {
    assert(x<height_ && y< width_);
    return data[width_ - 1 - y][x];
  }

  void DisplayMirroredFrameOnScreen(
      std::function<void(std::size_t, std::size_t, uint8_t)> DisplayFunctor) const {
    for(std::size_t i = 0; i < height_; i++) {
      for(std::size_t j = 0; j < width_; j++) {
        DisplayFunctor(i, j, GetMirrored(i, j));
      }
    }
  }
};

#endif // IMAGE_H
