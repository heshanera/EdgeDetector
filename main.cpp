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
    /*
    std::string inputImage = "imgs/test1.png"; 
    std::string skeletonizdImage = "imgs/skdtest1.png"; 
    
    std::string outputImage1 = "imgs/result1.png";
    std::string outputImage2 = "imgs/result2.png";
    std::string outputImage3 = "imgs/result3.png";
    std::string outputImage4 = "imgs/result4.png";
    
    Skeletonize skeletonize(inputImage,skeletonizdImage);
    
    DetectLine detectline1(skeletonizdImage,outputImage1,0);
    DetectLine detectline2(skeletonizdImage,outputImage2,1);
    DetectLine detectline3(skeletonizdImage,outputImage3,2);
    DetectLine detectline4(skeletonizdImage,outputImage4,3);
     * 
     */
    
    /*std::string outputImage5 = "imgs/result5.png";
    std::string outputImage6 = "imgs/result6.png";
    std::string outputImage7 = "imgs/result7.png";
    std::string outputImage8 = "imgs/result8.png";*/
    
    std::string canntIn1 = "imgs/test2.GIF",
                canntIn2 = "imgs/test3.GIF",
                canntIn3 = "imgs/test4.GIF",
                canntIn4 = "imgs/test5.GIF";
    
    std::string cannyGrayOut1 = "imgs/cannyGrayOut1.png",
                cannyGrayOut2 = "imgs/cannyGrayOut2.png",
                cannyGrayOut3 = "imgs/cannyGrayOut3.png",
                cannyGrayOut4 = "imgs/cannyGrayOut4.png";
    
    std::string cannyIntOut1 = "imgs/cannyIntOut1.png",
                cannyIntOut2 = "imgs/cannyIntOut2.png",
                cannyIntOut3 = "imgs/cannyIntOut3.png",
                cannyIntOut4 = "imgs/cannyIntOut4.png";
    
    std::string cannyOut1 = "imgs/cannyOut1.png",
                cannyOut2 = "imgs/cannyOut2.png",
                cannyOut3 = "imgs/cannyOut3.png",
                cannyOut4 = "imgs/cannyOut4.png";
    
    Canny canny1(canntIn1,cannyOut1);
    canny1.writeGrayScaleImage(cannyGrayOut1);
    canny1.writeIntermediateImage(cannyIntOut1);
    
    Canny canny2(canntIn2,cannyOut2);
    canny2.writeGrayScaleImage(cannyGrayOut2);
    canny2.writeIntermediateImage(cannyIntOut2);
    
    Canny canny3(canntIn3,cannyOut3);
    canny3.writeGrayScaleImage(cannyGrayOut3);
    canny3.writeIntermediateImage(cannyIntOut3);
    
    Canny canny4(canntIn4,cannyOut4);
    canny4.writeGrayScaleImage(cannyGrayOut4);
    canny4.writeIntermediateImage(cannyIntOut4);
    
    return 0; 
}
    
