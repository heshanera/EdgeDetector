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
   
    std::string inputImage = "imgs/inputImages/lines2.gif";   //test1.png"; 
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

    
    std::string canntIn1 = "imgs/inputImages/i1.gif",
                canntIn2 = "imgs/inputImages/i2.gif",
                canntIn3 = "imgs/inputImages/i3.gif",
                canntIn4 = "imgs/inputImages/i4.gif",
                canntIn5 = "imgs/inputImages/i5.gif",
                canntIn6 = "imgs/inputImages/i6.gif",
                canntIn7 = "imgs/inputImages/i7.gif",
                canntIn8 = "imgs/inputImages/i8.jpg";
                
    
    std::string cannyGrayOut1 = "imgs/cannyGrayOut1.png",
                cannyGrayOut2 = "imgs/cannyGrayOut2.png",
                cannyGrayOut3 = "imgs/cannyGrayOut3.png",
                cannyGrayOut4 = "imgs/cannyGrayOut4.png",
                cannyGrayOut5 = "imgs/cannyGrayOut5.png",
                cannyGrayOut6 = "imgs/cannyGrayOut6.png",
                cannyGrayOut7 = "imgs/cannyGrayOut7.png",
                cannyGrayOut8 = "imgs/cannyGrayOut8.png";
                
    
    std::string cannyIntOut1 = "imgs/cannyIntOut1.png",
                cannyIntOut2 = "imgs/cannyIntOut2.png",
                cannyIntOut3 = "imgs/cannyIntOut3.png",
                cannyIntOut4 = "imgs/cannyIntOut4.png",
                cannyIntOut5 = "imgs/cannyIntOut5.png",
                cannyIntOut6 = "imgs/cannyIntOut6.png",
                cannyIntOut7 = "imgs/cannyIntOut7.png",
                cannyIntOut8 = "imgs/cannyIntOut8.png"; 
    
    std::string cannyOut1 = "imgs/cannyOut1.png",
                cannyOut2 = "imgs/cannyOut2.png",
                cannyOut3 = "imgs/cannyOut3.png",
                cannyOut4 = "imgs/cannyOut4.png",
                cannyOut5 = "imgs/cannyOut5.png",
                cannyOut6 = "imgs/cannyOut6.png",
                cannyOut7 = "imgs/cannyOut7.png",
                cannyOut8 = "imgs/cannyOut8.png";
    
    Canny canny;
    
    canny.detectLines(canntIn1,cannyOut1,2);
    canny.writeGrayScaleImage(cannyGrayOut1);
    canny.writeIntermediateImage(cannyIntOut1);
    
    canny.detectLines(canntIn2,cannyOut2,1);
    canny.writeGrayScaleImage(cannyGrayOut2);
    canny.writeIntermediateImage(cannyIntOut2);
    
    canny.detectLines(canntIn3,cannyOut3,2);
    canny.writeGrayScaleImage(cannyGrayOut3);
    canny.writeIntermediateImage(cannyIntOut3);
    
    canny.detectLines(canntIn4,cannyOut4,1);
    canny.writeGrayScaleImage(cannyGrayOut4);
    canny.writeIntermediateImage(cannyIntOut4);
    
    canny.detectLines(canntIn5,cannyOut5,2);
    canny.writeGrayScaleImage(cannyGrayOut5);
    canny.writeIntermediateImage(cannyIntOut5);
    
    canny.detectLines(canntIn6,cannyOut6,1);
    canny.writeGrayScaleImage(cannyGrayOut6);
    canny.writeIntermediateImage(cannyIntOut6);
    
    canny.detectLines(canntIn7,cannyOut7,2);
    canny.writeGrayScaleImage(cannyGrayOut7);
    canny.writeIntermediateImage(cannyIntOut7);
    
    canny.detectLines(canntIn8,cannyOut8,1);
    canny.writeGrayScaleImage(cannyGrayOut8);
    canny.writeIntermediateImage(cannyIntOut8);
    
    return 0; 
}
    
