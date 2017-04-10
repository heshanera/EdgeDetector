/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectLine.cpp
 * Author: heshan
 * 
 * Created on April 10, 2017, 9:06 PM
 */
#include <Magick++.h>
#include <iostream>

#include "DetectLine.h"

using namespace std; 
using namespace Magick; 

DetectLine::DetectLine() {}

DetectLine::DetectLine(const DetectLine& orig) {}

DetectLine::~DetectLine() {}

int DetectLine::initializeImage(string path,char **argv){
    
    
    InitializeMagick(*argv);
    Image image;
    try { 
      
        image.read(path);
        //image.type( GrayscaleType );
        //image.modifyImage();

        int w = image.columns();
        int h = image.rows();
        int range = pow(2, image.modulusDepth());
        PixelPacket *pixels = image.getPixels(0, 0, w, h);
        int row = 0;
        int column = 0;
        Color color = pixels[w * row + column];

        // creating the pixel matrix
        this->imageMatrix = new float*[h];for(int i = 0; i < h; ++i) this->imageMatrix[i] = new float[w];
        this->width = w; this->height = h;
        this->range = range;
        
        for(row = 0; row < h-1; row++)
        {
          for(column = 0; column < w-1; column++)
          {
            Color color = pixels[w * row + column];
            //std::cout << (color.redQuantum() / range) << " ";
            this->imageMatrix[row][column] = (color.redQuantum() / range);
          }   
          //std::cout<< endl;
        }    
        
    } catch( Exception &error_ ) { 
        cout << "Caught exception: " << error_.what() << endl; 
        return 1; 
    } 
    return 0; 

}

int DetectLine::printImageMatrix(){
    
    for(int row = 0; row < (this->height)-1; row++)
    {
        for(int column = 0; column < (this->width)-1; column++)
        {
            //std::cout << (color.redQuantum() / range);
            //std::cout<< endl;
            std::cout<<this->imageMatrix[row][column]<<" ";
        } 
        std::cout<< endl;
    }    

}

int DetectLine::writeImage(std::string path){

    /*
    Image image;
    //image.
    
    image.setPixels(const ssize_t x_, const ssize_t y_, const size_t columns_, const size_t rows_);
    
    image.syncPixels();
    image.write("horse.jpg");
     */
    
    Image image("test1.GIF"); 
    // Ensure that there are no other references to this image.
    image.modifyImage();
    // Set the image type to TrueColor DirectClass representation.
    image.type(TrueColorType);
    // Request pixel region with size 60x40, and top origin at 20x30 
    ssize_t columns = 60; 
    Quantum *pixel_cache = image.getPixels(20,30,columns,40); 
    // Set pixel at column 5, and row 10 in the pixel cache to red. 
    ssize_t column = 5; 
    ssize_t row = 10; 
    Quantum *pixel = pixel_cache+row*columns+column; 
    *pixel = Color("red"); 
    // Save changes to underlying image .
    image.syncPixels();
    image.write("horse.png");
    
    
}