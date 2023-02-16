#include <stdio.h>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/core/utility.hpp>
#include<iostream>

using namespace cv;
using std::cout;

int threshold_value = 0;
int threshold_type = 3;
int threshold_OTSU = 0;
int const max_OTSU =1;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat image, image_gray, threshold_image,otsu_image;
const char* window_name = "Threshhold Image";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
const char* trackbar_OTSU = "THRESH_OTSU";

static void Threshold_function( int, void*)
{
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    if(threshold_OTSU == 1){ // if OTSU value set to 1, method change to OTSU
      threshold( image_gray, threshold_image, threshold_value, max_binary_value, THRESH_OTSU);
    }else{
      threshold( image_gray, threshold_image, threshold_value, max_binary_value, threshold_type);
    }
    imwrite("Threshold image.jpg",threshold_image);
    imshow(window_name,threshold_image);
}


int main(int argc , char **argv){

  String imageName("glaucoma.jpg"); // by default image
   if (argc > 1)
   {
       imageName = argv[1]; //get data path of image
   }
   image = imread( samples::findFile( imageName ), IMREAD_UNCHANGED ); // Load an image
   if (image.empty())
   {
      cout << "Cannot read the image: " << imageName << std::endl; // if there's no image, exit
      return -1;
   }
   namedWindow( window_name, WINDOW_AUTOSIZE ); // Create a window to display results

   cvtColor( image, image_gray, COLOR_BGR2GRAY,0 ); // Convert the image to Gray
   imwrite("gray image.jpg",image_gray);
   threshold( image_gray, otsu_image, threshold_value, max_binary_value, THRESH_OTSU);
   imwrite("otsu image.jpg",otsu_image);

   createTrackbar( trackbar_type,
                   window_name, &threshold_type,
                   max_type,Threshold_function); // Create a Trackbar to choose type of Threshold
   createTrackbar( trackbar_value,
                   window_name, &threshold_value,
                   max_value,Threshold_function); // Create a Trackbar to choose Threshold value
  createTrackbar( trackbar_OTSU,
                  window_name, &threshold_OTSU,
                  max_OTSU,Threshold_function); // Create a Trackbar to choose OTSU value

   Threshold_function(0,0);
   waitKey(0);

  return 0;
}
