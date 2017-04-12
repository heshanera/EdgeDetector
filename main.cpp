/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 10, 2017, 9:20 AM
 */

#include <iostream>
#include "DetectLine.h"
#include "Skeletonize.h"

/*
 * 
 */
int main(int argc,char **argv) 
{ 

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
    
    
    return 0; 
}

