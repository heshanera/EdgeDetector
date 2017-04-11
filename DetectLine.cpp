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


DetectLine::DetectLine() {}

DetectLine::DetectLine(const DetectLine& orig) {}

DetectLine::~DetectLine() {}

int DetectLine::initializeImage(std::string path,char **argv){
    
    Magick::InitializeMagick(*argv);
    Magick::Image image;
    try { 
      
        image.read(path);
        image.type( Magick::GrayscaleType );
        image.modifyImage();

        int w = image.columns();
        int h = image.rows();
        int range = pow(2, image.modulusDepth());
        Magick::PixelPacket *pixels = image.getPixels(0, 0, w, h);
        int row = 0;
        int column = 0;
        Magick::Color color = pixels[w * row + column];

        // creating the pixel matrix
        this->imageMatrix = new float*[h];for(int i = 0; i < h; ++i) this->imageMatrix[i] = new float[w];
        this->width = w; this->height = h;
        this->range = range;
        
        for(row = 0; row < h-1; row++)
        {
            for(column = 0; column < w-1; column++)
            {
                Magick::Color color = pixels[w * row + column];
                //std::cout << (color.redQuantum() / range) << " ";
                this->imageMatrix[row][column] = (color.redQuantum() / range);
            }   
          //std::cout<< endl;
        }    
        
    } catch(std::exception &error_ ) { 
        std::cout << "Caught exception: " << error_.what() << std::endl; 
        return 1; 
    } 
    return 0; 

}

int DetectLine::printImageMatrix(){
    
    for(int row = 0; row < (this->height)-1; row++)
    {
        for(int column = 0; column < (this->width)-1; column++)
        {
            std::cout<<this->imageMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }    
}

int DetectLine::printResultMatrix(){
    
    for(int row = 0; row < (this->height)-1; row++)
    {
        for(int column = 0; column < (this->width)-1; column++)
        {
            std::cout<<this->resultMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }    
}

int DetectLine::writeImage(std::string path){

    
    Magick::Image image;
    //image.
    
    image.setPixels(10, 20, 10, 10);
    //image.writePixels(QuantumTypes quantum_, unsigned char *destination_);
    
    image.syncPixels();
    //image.write("horse.jpg");
    
    
    /*
    Magick::Image image("test1.GIF"); 
    // Ensure that there are no other references to this image.
    image.modifyImage();
    // Set the image type to TrueColor DirectClass representation.
    image.type(Magick::TrueColorType);
    // Request pixel region with size 60x40, and top origin at 20x30 
    ssize_t columns = 20; 
    Magick::PixelPacket* pixel_cache = image.getPixels(20,20,columns,20); 
    // Set pixel at column 5, and row 10 in the pixel cache to red. 
    ssize_t column = 5; 
    ssize_t row = 10; 
    Magick::PixelPacket* pixel = pixel_cache+row*columns+column; 
    *pixel = Magick::Color("red"); 
    // Save changes to underlying image .
    image.syncPixels();
    image.write(path);
    */
    
}

int DetectLine::applyKernel(int kernelNo){

    float **tmpKernel;
    tmpKernel = new float*[3]; for(int i = 0; i < 3; i++) {tmpKernel[i] = new float[3];}
    
    // light lines against a dark background (0 - 3)
    float kernel[4][3][3] =  {   
                                   { {-1,-1,-1},{2,2,2},{-1,-1,-1} },
                                   { {-1,2,-1},{-1,2,-1},{-1,2,-1} },
                                   { {-1,-1,2},{-1,2,-1},{2,-1,-1} },
                                   { {2,-1,-1},{-1,2,-1},{-1,-1,2} } 
                                };
     

    
    this->resultMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->resultMatrix[i] = new float[this->width];
    
    
    for(int row = 0; row < (this->height)-4; row++)
    {
        for(int column = 0; column < (this->width)-4; column++)
        {
            
            double pSum = 0;
            for(int kernelRow = 0; kernelRow < 3; kernelRow++)
            {
                for(int kernelColumn = 0; kernelColumn < 3; kernelColumn++)
                {
                    pSum += (this->imageMatrix[row + kernelRow][column + kernelColumn]*kernel[kernelNo][kernelRow][kernelColumn]);
                    //std::cout<<kernel[kernelNo][kernelRow][kernelColumn]<<"  ";
                } 
            }
            this->resultMatrix[row][column] = pSum;
            //std::cout<<pSum<<" ";
        } 
        //std::cout<< std::endl;
    }   

}