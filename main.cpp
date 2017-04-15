/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 10, 2017, 9:20 AM
 */

#include <iostream>
#include "DetectLine.h"
#include "Skeletonize.h"
#include "Canny.h"

/*
 * 
 */
int main(int argc,char **argv) 
{ 
   
    std::string inputImage = "imgs/test1.png"; 
    std::string skeletonizdImage = "imgs/skdtest1.png"; 
    
    std::string outputImage1 = "imgs/result1.png",
                outputImage2 = "imgs/result2.png",
                outputImage3 = "imgs/result3.png",
                outputImage4 = "imgs/result4.png";
    
    Skeletonize skeletonize(inputImage,skeletonizdImage);
    
    DetectLine dln;
    dln.getLines(skeletonizdImage,outputImage1,0);
    dln.getLines(skeletonizdImage,outputImage2,1);
    dln.getLines(skeletonizdImage,outputImage3,2);
    dln.getLines(skeletonizdImage,outputImage4,3);

    
    std::string canntIn1 = "imgs/test2.GIF",
                canntIn2 = "imgs/test3.GIF",
                canntIn3 = "imgs/test4.GIF",
                canntIn4 = "imgs/test5.GIF",
                canntIn5 = "imgs/test6.GIF";
    
    std::string cannyGrayOut1 = "imgs/cannyGrayOut1.png",
                cannyGrayOut2 = "imgs/cannyGrayOut2.png",
                cannyGrayOut3 = "imgs/cannyGrayOut3.png",
                cannyGrayOut4 = "imgs/cannyGrayOut4.png",
                cannyGrayOut5 = "imgs/cannyGrayOut5.png";    
    
    std::string cannyIntOut1 = "imgs/cannyIntOut1.png",
                cannyIntOut2 = "imgs/cannyIntOut2.png",
                cannyIntOut3 = "imgs/cannyIntOut3.png",
                cannyIntOut4 = "imgs/cannyIntOut4.png",
                cannyIntOut5 = "imgs/cannyIntOut5.png";
    
    std::string cannyOut1 = "imgs/cannyOut1.png",
                cannyOut2 = "imgs/cannyOut2.png",
                cannyOut3 = "imgs/cannyOut3.png",
                cannyOut4 = "imgs/cannyOut4.png",
                cannyOut5 = "imgs/cannyOut5.png";
    
    Canny canny;
    
    canny.detectLines(canntIn1,cannyOut1,2);
    canny.writeGrayScaleImage(cannyGrayOut1);
    canny.writeIntermediateImage(cannyIntOut1);
    
    canny.detectLines(canntIn2,cannyOut2,1);
    canny.writeGrayScaleImage(cannyGrayOut2);
    canny.writeIntermediateImage(cannyIntOut2);
    
    canny.detectLines(canntIn3,cannyOut3,1);
    canny.writeGrayScaleImage(cannyGrayOut3);
    canny.writeIntermediateImage(cannyIntOut3);
    
    canny.detectLines(canntIn4,cannyOut4,1);
    canny.writeGrayScaleImage(cannyGrayOut4);
    canny.writeIntermediateImage(cannyIntOut4);
    
    canny.detectLines(canntIn5,cannyOut5,0);
    canny.writeGrayScaleImage(cannyGrayOut5);
    canny.writeIntermediateImage(cannyIntOut5);
    
    return 0; 
}
    
