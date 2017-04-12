/* 
 * File:   Skeletonize.cpp
 * Author: heshan
 * 
 * Created on April 11, 2017, 8:39 PM
 */
#include <iostream>
#include <Magick++.h>
#include "Skeletonize.h"

Skeletonize::Skeletonize() {}

Skeletonize::Skeletonize(const Skeletonize& orig) {}

Skeletonize::~Skeletonize() {}

int Skeletonize::initializeImage(std::string path){
    
    
    Magick::InitializeMagick(NULL);
    Magick::Image image(path);
    this->img = image;
    try { 
      
        image.type( Magick::GrayscaleType );
        image.modifyImage();

        int w = image.columns(),h = image.rows();
        int row = 0,column = 0;
        int range = pow(2, image.modulusDepth());
        
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

int Skeletonize::reconfPixels(){

    // creating the pixel matrix
    this->reconfedImageMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->reconfedImageMatrix[i] = new float[this->width];
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            if (this->imageMatrix[row][column] > 0 ) this->reconfedImageMatrix[row][column] = 1;
            else this->reconfedImageMatrix[row][column] = 0;
        } 
    }   
}    

int Skeletonize::getArticulationPoints(){
    
    this->resultMatrix = new float*[this->height];for(int i = 0; i < this->height; ++i) this->resultMatrix[i] = new float[this->width];
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            //reconfedImageMatrix[row-1][column-1];
            //reconfedImageMatrix[row-1][column+1];
            //reconfedImageMatrix[row+1][column-1];
            //reconfedImageMatrix[row+1][column+1];
            if ( (column == 0) || (column == (this->width)-1) || (row == 0) || (row == (this->height) -1) ) {
            
                resultMatrix[row][column] = reconfedImageMatrix[row][column];
                
            } else {
                
                if ((  reconfedImageMatrix[row-1][column] == 1) & 
                    (  reconfedImageMatrix[row][column-1] == 1) &
                    (  reconfedImageMatrix[row][column+1] == 1) & 
                    (  reconfedImageMatrix[row+1][column] == 1)    ) resultMatrix[row][column] = 2;
                else resultMatrix[row][column] = reconfedImageMatrix[row][column];  
            }
            
        } 
    }     
}

int Skeletonize::printReconfedMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->reconfedImageMatrix[row][column]<<" ";
        } 
        std::cout<<"\n";
    }   
}

int Skeletonize::printResultMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->resultMatrix[row][column]<<" ";
        } 
        std::cout<<"\n";
    }   
}