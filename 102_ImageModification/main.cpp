/**
 * @file main.cpp
 * @author M. Z.
 * @brief  Image Modification: This project will focus on the use of dynamic
allocation of arrays and file input/output, as well as separating implementation
into multiple files and some detecting & overcoming stream Input/Output issues.
 * @version 0.1
 * @date 2024-08-06
 *
 * @copyright Copyright (c) 2024
 *
Introduction of how images work -- PPM imagery

These images, unlike most other formats, are stored in an ASCII text file. More
complicated image formats (like .gif and .jpg) are stored in a binary file and
use sophisticated compression algorithms to make the file size smaller. A .ppm
image can contain the exact same image as a .gif or .jpg, but it would likely be
significantly larger in file size.

Most image types start with two special characters, which are referred to as
that image type's "magic number" (not to be confused with the magic numbers
we’ve talked about as being bad style in programming). A computer program can
determine which type of image it is based on the value of these first two
characters. For a .ppm image, the magic number is "P3", which simply allows an
image viewing program to determine that this file is a PPM image and should be
read using the PPM format.

Since a 100 pixel image may be an image of 25 rows and 4 columns, or 10 rows and
10 columns (or any other such combination) you need to know the specific size of
the image. Therefore, after the magic number, the next two elements of the .ppm
file are the width of the image, followed by the height of the image. Obviously,
both of these values should be integers, since they both are in units of "number
of pixels". (note: width comes first, and height comes second! People always get
this mixed up, so take care with the order…)

The next value is also an integer, and is simply the maximum value in the color
descriptions. For this project, you will use 255 as the maximum number. With a
maximum of 10, you are only allowed 10 shades of gray, and 10^3 unique colors
which would not allow you to generate a very photographic looking image, but if
your maximum value is 255, you could get a much wider range of colors (255^3).

The only thing left is a description of each and every pixel in the image. The
pixel in the upper left corner of the image comes first. The rest of the first
row follows, and then the first pixel of the second row comes after that. This
pattern continues until every pixel has been described (in other words, there
should be rowscols color values in the .ppm file). As mentioned above, each
pixel is described with three integers (red, green, blue), so a 4 row by 4
column color image requires 44*3=48 integers to describe the pixels.

Once you create these images, you can view them many ways. There are many freely
available programs that will display PPM images directly (I often use one called
"IrfanView" on Windows (should be able to download this free from download.com)
and either "xv" or ImageMagick's "display" on Linux). Another alternative is to
convert the image to a JPEG image, which will allow you to display the image via
a web browser. One way to convert a PPM to JPG is to use the Linux command
"cjpeg" like this.

Introduction of Implementation

For this we will implement a few algorithms to modify an image. However, after
completing the project, you will be able to add any number of your own
algorithms to modify imagery in any number of ways. Following are descriptions
of the algorithms you are required to implement:

First, you will need to allow rectangles to be drawn on an image. Rectangle
outlines may be placed on an image to draw attention to a specific area, or
filled rectangles may be placed on an image to block out a specific area. Both
of these operations will be supported in this project.

Second, and more interestingly, an image may be annotated with a “pattern”. A
pattern, while rectangular overall, contains a description of a shape that is to
be placed on an image. A pattern consists of a rectangle of only zeros and ones.
When a pattern is placed over an image, the values in the pattern each fall over
a specific pixel in the original image. A value of one in a pattern indicates
that the pixel under it should be modified to be a certain color that is
specified by the user. A zero in a pattern indicates that the pixel under it
should NOT be affected by the pattern. Its original value is left intact,
resulting in a sort of transparency.

Patterns are contained in text files of the following format: The first value is
an integer representing the number of columns in the rectangular pattern. The
second value is an integer representing the number of rows in the rectangular
pattern. What follows is a collection of zeros and ones that is (rows * columns)
in length. The placement of such patterns on an image will be supported in this
project. This capability allows you to annotate an image with any shape you
wish, regardless of what it looks like.

The final image modification algorithm you will implement is the insertion of
another (presumably smaller) PPM image at a specified location within the image
being modified. This insertion simply reads another PPM image from a file and
inserts the image contents where the user desires. PPM images are, by
definition, rectangular. Since oftentimes, the image you want to insert is not
rectangular, you must support a transparency color, such that any pixel in the
image to be inserted which is the transparency color does not change the
original image, but pixels that are not the transparency color will be used to
replace the pixel value in the original image. Note that this is very similar to
the use of a pattern, described above, except that patterns can only be one
color, while inserted images can have as many colors as the PPM allows.

At any stage, you must allow the user to output a PPM image file in its current
state from the main menu. The user may want to output an image after each change
made, or just once when all updates have been performed. Since the option of
outputting an image is available on the main menu, this functionality will be
supported in this project.

All of your global constants must be declared and initialized in a file named
"constants.h". This file will not have a corresponding .cpp file, since it will
not contain any functions or class definitions. Make sure you put all your
global constants in this file, and avoid magic numbers. Since you now know about
dynamic allocation, the image pixels will be allocated using the new operator,
using exactly the amount of space required for the image (for example, a smaller
image will use less memory than a larger image). Therefore, there is no
practical limit to the size of the image allowed.
 */

#include <fstream>
#include <iostream>

using namespace std;

#include "ColorImageClass.h"

int main() {
  string fileNamePpm, fileNameContPtrn, fileNamePpmInsrt, fileNamePpmOut;
  int mainMenuCount, mainMenuChoic, upLeftRecRow, upLeftRecClmn, mxValColor;

  cout << "Enter string for PPM image file name to load: ";
  cin >> fileNamePpm;

  ColorImageClass ppmImage;
  ppmImage.getChkPpmFile(mxValColor, fileNamePpm);
  RowColumnClass rowColImageUpLeft;
  RowColumnClass rowColImageLwrLeft;
  ColorClass colorImage;
  colorImage.setMaxColor(mxValColor);

  do {
    mainMenuCount = 0;

    cout << ++mainMenuCount << ". Annotate image with rectangle" << endl;
    cout << ++mainMenuCount << ". Annotate image with pattern from file"
         << endl;
    cout << ++mainMenuCount << ". Insert another imag" << endl;
    cout << ++mainMenuCount << ". Write out current image" << endl;
    cout << ++mainMenuCount << ". Exit the program" << endl;

    cout << "Enter int for main menu choice: ";
    ppmImage.validIntInput(mainMenuChoic, mainMenuCount);

    if (mainMenuChoic == 1) {
      ppmImage.rectSpecMtd(rowColImageUpLeft, rowColImageLwrLeft);

      ppmImage.colorChoice(mainMenuChoic, colorImage);

      ppmImage.recFillOption(rowColImageUpLeft, rowColImageLwrLeft, colorImage);

    } else if (mainMenuChoic == 2) {
      cout << "Enter string for file name containing pattern: ";
      cin >> fileNameContPtrn;

      cout << "Enter upper left corner of pattern row and column: ";
      cin >> upLeftRecRow;
      cin >> upLeftRecClmn;

      rowColImageUpLeft.setRowCol(upLeftRecRow, upLeftRecClmn);

      ppmImage.colorChoice(mainMenuChoic, colorImage);

      ppmImage.getChkTxtFile(rowColImageUpLeft, colorImage, fileNameContPtrn);

    } else if (mainMenuChoic == 3) {
      cout << "Enter string for file name of PPM image to insert: ";
      cin >> fileNamePpmInsrt;

      cout << "Enter upper left corner to insert image row and column: ";
      cin >> upLeftRecRow;
      cin >> upLeftRecClmn;

      rowColImageUpLeft.setRowCol(upLeftRecRow, upLeftRecClmn);

      ppmImage.colorChoice(mainMenuChoic, colorImage);

      ppmImage.getChkPpmInsrt(rowColImageUpLeft, colorImage, fileNamePpmInsrt);

    } else if (mainMenuChoic == 4) {
      cout << "Enter string for PPM file name to output: ";
      cin >> fileNamePpmOut;

      ppmImage.writeOutPpmFile(mxValColor, fileNamePpmOut);
    }
  } while (mainMenuChoic != 5);

  cout << "Thank you for using this program" << endl;

  return 0;
}
