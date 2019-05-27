Frame Mirroring
=====================

The goal of this implementation is to mirror (flip left-right) a single frame to be displayed by a media player.

- For the sake of simplicity, let's consider only grayscale square images.
- We assume that `N` is **not** the total number of pixels in the image, but rather the `width` and the `height`. 
- We are only considering single-threaded solutions.


Three options have been implemented:
1. Iterate through the rows and reverse each one of them. The time complexity is `O(N^2)`
2. Reverse the columns, by taking advantage of the memory layout; and only pointers are swapped. The time complexity is `O(N)`
3. Provide a method that transforms the coordinates `(x, y) ==> (x, width - 1 - y)` to get the pixel value.

<p align="center">
  <img src="https://github.com/FranckyN/FrameMirroring/blob/master/demo10-10.GIF?raw=true" alt="Demo Frame Mirroring"/>
</p>


Usage:
---------

Create and use an instance of the **Image** class (Image.h).

The file `main.cpp` shows how to use the structure Image.

- Edit the file as needed.

At the project root directory:

- to clean type `make clean`
- to build type `make`
- to run option 2 type `./fmirroringtest 2`