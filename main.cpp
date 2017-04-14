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
    
    std::string inputImage2 = "imgs/test2.GIF";
    std::string outputImage2 = "imgs/testCanny.png";
    
    std::string outputImage5 = "imgs/result5.png";
    std::string outputImage6 = "imgs/result6.png";
    std::string outputImage7 = "imgs/result7.png";
    std::string outputImage8 = "imgs/result8.png";
    
    Canny canny(inputImage2,outputImage2,1);
    
    DetectLine detectline5(outputImage2,outputImage5,0);
    DetectLine detectline6(outputImage2,outputImage6,1);
    DetectLine detectline7(outputImage2,outputImage7,2);
    DetectLine detectline8(outputImage2,outputImage8,3);
    
    
    return 0; 
}

