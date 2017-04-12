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

    /* 
    DetectLine dl;
    
    dl.initializeImage("imgs/test1.GIF");
    dl.applyKernel(2);
    dl.writeImage("imgs/result.png");
    */
    
    /*
    dl.initializeImage("imgs/test2.GIF");
    dl.applyKernel(0);
    dl.writeImage("imgs/result2.png");
    */
    
    /*
    dl.initializeImage("imgs/test3.GIF");
    dl.applyKernel(1);
    dl.writeImage("imgs/result3.png");
    */
    
    std::string inputImage = "imgs/test1.GIF"; 
    std::string skeletonizdImage = "imgs/skdtest1.png"; 
    std::string outputImage = "imgs/result.png"; 
    
    Skeletonize skeletonize(inputImage,skeletonizdImage);
    
    
    
    return 0; 
}

