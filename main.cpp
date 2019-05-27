//============================================================================
// Author      : Franck Nassé - May 27, 2019
// Version     : v1.0
// Copyright   : Copyright (c) 2019, Franck Nassé. All rights reserved.
// Description : Main
//============================================================================
#include <stdio.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "Image.h"

void ReadInput(int&, char**, int);
void Option1(Image&);
void Option2(Image&);
void Option3(Image&);
void FillImage(Image&);
void ExecuteOption(int, Image&);

/**
 * @brief Main function, the function accepts one command-line argument
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
  int option = -1;
  ReadInput(option, argv, argc);

  // Generating sample image
  const int N = 10;
  Image img(N, N);
  FillImage(img);

  std::cout << "Frame received:" << std::endl;
  img.Print();
  std::cout << std::endl;
  
  ExecuteOption(option, img);
  return 0;
}

/**
 * @brief Executes one of the algorithms
 * @param option integer [1,3]
 * @param img
 */
void ExecuteOption(int option, Image& img) {
  switch(option) {
  case 1:
    Option1(img);
    break;
  case 2:
    Option2(img);
    break;
  case 3:
    Option3(img);
    break;
  default:
    std::cerr << "Unknown option" << std::endl;
    break;
  }
}

/**
 * @brief Generates image values with numbers in the range [0, 255]
 * @param img
 */
void FillImage(Image& img) {
  for(std::size_t i = 0; i < img.NumRows(); i++) {
    for(std::size_t j = 0; j < img.NumCols(); j++) {
      img.Set(i, j, (uint8_t)((j + 1) % std::numeric_limits<uint8_t>::max()));
    }
  }
}

/**
 * @brief Option 1: Reverting the image line by line,
          This method will always work irrespective of the image memory layout.
          The time complexity is O(N^2)
 * @param img
 */
void Option1(Image& img) {
  img.MirrorFrameLineInPlace();
  std::cout << "MirrorFrameLineInPlace - Mirrorring: " << std::endl;
  std::cout << std::endl;
  img.Print();
  std::cout << std::endl;
}

/**
 * @brief Option 2: Since the image is stored as an array of pointers to the
          columns, the algorithm just reverses the array (std::vector) without
          touching the pixel values.  The time complexity is O(N)
 * @param img
 */
void Option2(Image& img) {
  img.MirrorFrameInPlace();
  std::cout << "MirrorFrameInPlace Mirrorring: " << std::endl;
  std::cout << std::endl;
  img.Print();
}

/**
 * @brief Option 3: There is no processing involved, the media player can just
          render the image on the screen directly  pixel by pixel by calling the
          method Image::GetMirrored. In the example below, the image is printed
          on the console.  An alternative would be to provide the media player
          rendering function to the method  Image::DisplayMirroredFrameOnScreen
 * @param img
 */
void Option3(Image& img) {
  std::cout << "GetMirrored Mirrorring:" << std::endl;
  std::cout << std::endl;
  for(std::size_t i = 0; i < img.NumRows(); i++) {
    for(std::size_t j = 0; j < img.NumCols(); j++) {
      std::cout << (int)img.GetMirrored(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Reads the argument of the program
 * @param option integer to read
 * @param argv arguments array
 * @param argc number of arguments
 */
void ReadInput(int& option, char** argv, int argc) {
  if(argc > 1) {
    std::istringstream input(argv[1]);
    if(!(input >> option)) {
      std::cerr << "Wrong option: " << argv[1] << std::endl;
    } else if(!input.eof()) {
      std::cerr << "Additional characters " << std::endl;
    }
  }
}