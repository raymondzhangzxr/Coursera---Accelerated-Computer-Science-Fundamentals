#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;
using std::cout;
using std::endl;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
 for (double x = 0; x < image.width(); x++) {
    for (double y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      double xdist = (x-centerX);
      double ydist = (y-centerY);
      double dist = sqrt(pow(xdist, 2.0)+pow(ydist, 2.0));
      // cout << "xdist is" << endl;
      // cout << xdist << endl;
      
      // cout << "ydist is" << endl;
      // cout << ydist << endl;
      
      // cout << "distance is" << endl;
      // cout << dist << endl;
      
      // cout << "original l is " << endl;
      // cout << pixel.l << endl;
      if (dist>160){
        pixel.l = 0.2*pixel.l;
      }
      else{
        pixel.l =(1-dist*0.005)*pixel.l;
      }
      // cout << "After l is " << endl;
      // cout << pixel.l << endl;
    }
}
  return image;

}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      double diffOrange = abs(pixel.h-11);
      if (diffOrange>180){
        diffOrange= 360-diffOrange;
      }
      double diffBlue = abs(pixel.h-216);
      if (diffBlue>180){
        diffBlue= 360-diffBlue;
      }

      if (diffBlue<diffOrange){
        pixel.h = 216;
        
      }
      else{
        pixel.h = 11;
      }
    }
  }

  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  for (unsigned x = 0; x < firstImage.width(); x++) {
    for (unsigned y = 0; y < firstImage.height(); y++) {
      HSLAPixel & pixel = firstImage.getPixel(x, y);
      HSLAPixel & pixel2 = secondImage.getPixel(x, y);
      if(pixel2.l==1){
        pixel.l = pixel.l+0.2;
        if(pixel.l>1){
          pixel.l = 1;
        }
        
        }
    }
  }
  return firstImage;
}
