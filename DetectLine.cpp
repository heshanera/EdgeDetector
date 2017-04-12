/* 
 * File:   DetectLine.cpp
 * Author: heshan
 * 
 * Created on April 10, 2017, 9:06 PM
 */
#include <iostream>
#include <Magick++.h>
#include "DetectLine.h"


DetectLine::DetectLine(std::string inputImage, std::string outputImage, int kernelNo) {

    initializeImage(inputImage);
    applyKernel(kernelNo);
    writeImage(outputImage);

}

DetectLine::DetectLine(const DetectLine& orig) {}

DetectLine::~DetectLine() {}

int DetectLine::initializeImage(std::string path){
    
    
    Magick::InitializeMagick(NULL);
    Magick::Image image(path);
    this->img = image;
    try { 
      
        image.type( Magick::GrayscaleType );
        image.modifyImage();

        int w = image.columns(),h = image.rows();
        int row = 0,column = 0;
        int range = 256; //pow(2, image.modulusDepth());
        
        Magick::PixelPacket *pixels = image.getPixels(0, 0, w, h);

        // creating the pixel matrix
        this->imageMatrix = new float*[h];for(int i = 0; i < h; ++i) this->imageMatrix[i] = new float[w];
        // storing meta data
        this->width = w; this->height = h;
        this->range = range;
        
        for(row = 0; row < h; row++)
        {
            for(column = 0; column < w; column++)
            {
                Magick::Color color = pixels[w * row + column];
                this->imageMatrix[row][column] = (color.redQuantum()/range)/256;
            }   
            //std::cout<< std::endl;
        }    
        
    } catch(std::exception &error_ ) { 
        std::cout << "Caught exception: " << error_.what() << std::endl; 
        return 1; 
    } 
    
    return 0; 

}

int DetectLine::applyKernel(int kernelNo){

    float **tmpKernel;
    tmpKernel = new float*[3]; for(int i = 0; i < 3; i++) {tmpKernel[i] = new float[3];}
    
    /**
     * light lines against a dark background (0 - 3)
     * 0 - horizontal
     * 1 - vertical
     * 2 - diagonal (/)
     * 3 - diagonal (\)
     * 
     **/ 
    float kernel[4][3][3] =    {   
                                   { {-1,-1,-1},{2,2,2},{-1,-1,-1} },
                                   { {-1,2,-1},{-1,2,-1},{-1,2,-1} },
                                   { {-1,-1,2},{-1,2,-1},{2,-1,-1} },
                                   { {2,-1,-1},{-1,2,-1},{-1,-1,2} } 
                                };
     

    
    this->resultMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->resultMatrix[i] = new float[this->width];
    
    
    for(int row = 0; row < (this->height)-3; row++)
    {
        for(int column = 0; column < (this->width)-3; column++)
        {
            
            float pSum = 0;
            for(int kernelRow = 0; kernelRow < 3; kernelRow++)
            {
                for(int kernelColumn = 0; kernelColumn < 3; kernelColumn++)
                {
                    pSum += (float)(this->imageMatrix[row + kernelRow][column + kernelColumn]*kernel[kernelNo][kernelRow][kernelColumn]);
                } 
            }
            this->resultMatrix[row][column] = pSum;
        } 
    }   
}

int DetectLine::writeImage(std::string path){

    Magick::Image image;
    image = this->img;
    image.modifyImage();
    image.type(Magick::TrueColorType);
    ssize_t columns = this->width; 
    Magick::PixelPacket *pixel_cache = image.getPixels(0,0,this->width, this->height); 
    
    for(int i = 0; i < this->width; i++)
    {
        for(int j = 0; j < this->height; j++)
        {
            // thresholding the values
            float pVal = this->resultMatrix[j][i];
            if ( pVal > 2 ) { pVal = 1; }
            else pVal = 0;
            
            Magick::ColorGray gColor(pVal);
            Magick::PixelPacket *pixel = pixel_cache+j*columns+i;    
            *pixel = gColor;
        } 
    }
    image.syncPixels();
    image.write(path);
    
    return 0; 
   
}

int DetectLine::printImageMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->imageMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }    
}

int DetectLine::printResultMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->resultMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }    
}