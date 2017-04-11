/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    dl.initializeImage("test1.GIF");
    //dl.printImageMatrix();
    
    dl.applyKernel(0);
    //dl.printResultMatrix();
    
    dl.writeImage("test1.GIF");
    
    return 0; 
}

