/* 
 * File:   Canny.cpp
 * Author: heshan
 * 
 * Created on April 14, 2017, 11:36 PM
 */

#include <iostream>
#include <Magick++.h>
#include "Canny.h"

Canny::Canny(std::string inputImage, std::string outputImage, int smoothType) {

    initializeImage(inputImage);
    gaussianFilter();
    //printResultMatrix();
    threshold();
    writeImage(outputImage);
 
}

Canny::Canny(const Canny& orig) {}

Canny::~Canny() {}

int Canny::initializeImage(std::string path){
    
    
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

int Canny::gaussianFilter(){

    
    /**
     *          | 1 4  7  4  1 |
     *          | 4 16 26 16 4 |
     *    1/273 | 7 26 41 26 7 |
     *          | 4 16 26 16 4 |
     *          | 1 4  7  4  1 |
     * 
     **/ 
    
    float kernel[5][5] =    {   
                                { 1, 4,  7,  4,  1 },
                                { 4, 16, 26, 16, 4 },
                                { 7, 26, 41, 26, 7 },
                                { 4, 16, 26, 16, 4 }, 
                                { 1, 4,  7,  4,  1 }
                            };
     

    
    this->resultMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->resultMatrix[i] = new float[this->width];
    
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum = 0;
            if ( (row >= (this->height)-5) || (column >= (this->width)-5) ){
            
                this->resultMatrix[row][column] = this->imageMatrix[row][column];
            
            } else {
                
                for(int kernelRow = 0; kernelRow < 5; kernelRow++)
                {
                    for(int kernelColumn = 0; kernelColumn < 5; kernelColumn++)
                    {
                        pSum += (float)(this->imageMatrix[row + kernelRow][column + kernelColumn]*kernel[kernelRow][kernelColumn]);
                    } 
                }
                this->resultMatrix[row][column] = ( pSum/273 );
            
            }
            
            
            
        } 
    } 
    
    return 0;
}

int Canny::meanFilter(){

    
    /**
     *          | 1 4  7  4  1 |
     *          | 4 16 26 16 4 |
     *    1/273 | 7 26 41 26 7 |
     *          | 4 16 26 16 4 |
     *          | 1 4  7  4  1 |
     * 
     **/ 
    
    float kernel[5][5] =    {   
                                { 1, 4,  7,  4,  1 },
                                { 4, 16, 26, 16, 4 },
                                { 7, 26, 41, 26, 7 },
                                { 4, 16, 26, 16, 4 }, 
                                { 1, 4,  7,  4,  1 }
                            };
     

    
    this->resultMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->resultMatrix[i] = new float[this->width];
    
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum = 0;
            if ( (row >= (this->height)-5) || (column >= (this->width)-5) ){
            
                this->resultMatrix[row][column] = this->imageMatrix[row][column];
            
            } else {
                
                for(int kernelRow = 0; kernelRow < 5; kernelRow++)
                {
                    for(int kernelColumn = 0; kernelColumn < 5; kernelColumn++)
                    {
                        pSum += (float)(this->imageMatrix[row + kernelRow][column + kernelColumn]*kernel[kernelRow][kernelColumn]);
                    } 
                }
                this->resultMatrix[row][column] = ( pSum/273 );
            
            }
            
            
            
        } 
    } 
    
    return 0;
}

int Canny::threshold(){

    float pVal;
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            pVal = this->resultMatrix[row][column];
            if (pVal > 0.5) pVal = 1; else pVal = 0;
            this->resultMatrix[row][column] = pVal;
        } 
    }
}

int Canny::writeImage(std::string path){

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
            float pVal = this->resultMatrix[j][i];
            Magick::ColorGray gColor(pVal);
            Magick::PixelPacket *pixel = pixel_cache+j*columns+i;    
            *pixel = gColor;
        } 
    }
    image.syncPixels();
    image.write(path);
    
    return 0; 
}

int Canny::printResultMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->resultMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }  
    return 0;  
}

