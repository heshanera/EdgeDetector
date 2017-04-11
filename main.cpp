/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 10, 2017, 9:20 AM
 */

#include <iostream>
#include "DetectLine.h"

/*
 * 
 */
int main(int argc,char **argv) 
{ 

    DetectLine dl;
    
    dl.initializeImage("imgs/test1.GIF");
    dl.applyKernel(2);
    dl.writeImage("imgs/result.png");
    
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
    
    return 0; 
}

