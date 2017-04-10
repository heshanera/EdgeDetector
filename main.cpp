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

#include <Magick++.h>
#include <iostream>
#include "DetectLine.h"

using namespace std; 
using namespace Magick; 

/*
 * 
 */
int main(int argc,char **argv) 
{ 

    DetectLine dl;
    dl.initializeImage("test1.GIF",argv);
    dl.printImageMatrix();
    dl.writeImage("");
    
    return 0; 
}

