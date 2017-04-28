/* 
 * File:   Skeletonize.cpp
 * Author: heshan
 * 
 * Created on April 11, 2017, 8:39 PM
 */
#include <iostream>
#include <Magick++.h>
#include "Skeletonize.h"

Skeletonize::Skeletonize(std::string inputImage, std::string outputImage) {
    
    initializeImage(inputImage);
    reconfPixels();
    
    while(1) 
    {    
        getArticulationPoints();
        //printBoundaryPixelMatrix();
        removeBoundaryPixels();
        //printBoundaryPixelMatrix();
        //printReconfedMatrix();
        if (this->interiorPixels == 0) break;
    }    
    
    for(int i = 0; i < 20; i++){
        getArticulationPointsPhase2();
        removeBoundaryPixelsPhase2();
    }
    
    for(int i = 0; i < 5; i++){
    }
    
    //printBoundaryPixelMatrix();
    //printReconfedMatrix();
    
    writeImage(outputImage);
    
}

Skeletonize::Skeletonize(const Skeletonize& orig) {}

Skeletonize::~Skeletonize() {}

int Skeletonize::initializeImage(std::string path){
    
    
    Magick::InitializeMagick(NULL);
    Magick::Image image(path);
    this->img = image;
    this->interiorPixels = 0;
    
    try { 
      
        image.type( Magick::GrayscaleType );
        image.modifyImage();

        int w = image.columns(),h = image.rows();
        int row = 0,column = 0;
        int range = pow(2, image.modulusDepth());
        
        Magick::PixelPacket *pixels = image.getPixels(0, 0, w, h);

        // creating the pixel matrices
        this->imageMatrix = new float*[h];for(int i = 0; i < h; ++i) this->imageMatrix[i] = new float[w];
        this->reconfedImageMatrix = new float*[h];for(int i = 0; i < h; ++i) this->reconfedImageMatrix[i] = new float[w];
        this->boundaryPixelMatrix = new float*[h];for(int i = 0; i < h; ++i) this->boundaryPixelMatrix[i] = new float[w];
    
        
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

    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            if (this->imageMatrix[row][column] > 0.7 ) this->reconfedImageMatrix[row][column] = 1; // thresholding
            else this->reconfedImageMatrix[row][column] = 0;
        } 
    }   
    return 0;
}    

int Skeletonize::getArticulationPoints(){
    
    
    int tmpInPix = this->interiorPixels;
    this->interiorPixels = 0;
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            //reconfedImageMatrix[row-1][column-1];
            //reconfedImageMatrix[row-1][column+1];
            //reconfedImageMatrix[row+1][column-1];
            //reconfedImageMatrix[row+1][column+1];
            if ( (column == 0) || (column == (this->width)-1) || (row == 0) || (row == (this->height) -1) ) {
            
                boundaryPixelMatrix[row][column] = reconfedImageMatrix[row][column];
                
            } else {
                
                if ((  reconfedImageMatrix[row-1][column] == 1) & 
                    (  reconfedImageMatrix[row][column-1] == 1) &
                    (  reconfedImageMatrix[row][column+1] == 1) & 
                    (  reconfedImageMatrix[row+1][column] == 1)    ) { boundaryPixelMatrix[row][column] = 2; this->interiorPixels++;}
                else boundaryPixelMatrix[row][column] = reconfedImageMatrix[row][column];  
            }
            
        } 
    }
    if ( tmpInPix == this->interiorPixels ) this->interiorPixels = 0;
    return 0;
}

int Skeletonize::getArticulationPointsPhase2(){
    
    
    int tmpInPix = this->interiorPixels;
    this->interiorPixels = 0;
    int tmpPoints;
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            
            tmpPoints = 0;
            if ( (column == 0) || (column == (this->width)-1) || (row == 0) || (row == (this->height) -1) ) {
            
                boundaryPixelMatrix[row][column] = reconfedImageMatrix[row][column];
                
            } else {
                
                if (  reconfedImageMatrix[row-1][column] == 1) tmpPoints++;
                if (  reconfedImageMatrix[row][column-1] == 1) tmpPoints++;
                if (  reconfedImageMatrix[row][column+1] == 1) tmpPoints++;
                if (  reconfedImageMatrix[row+1][column] == 1) tmpPoints++;   
                    
                if (tmpPoints == 3) { boundaryPixelMatrix[row][column] = 3; reconfedImageMatrix[row][column] = 1; this->interiorPixels++;}
                else boundaryPixelMatrix[row][column] = reconfedImageMatrix[row][column];  
            }
            
        } 
    }
    if ( tmpInPix == this->interiorPixels ) this->interiorPixels = 0;
    return 0;
}

int Skeletonize::removeBoundaryPixels(){
    
    for(int row = 1; row < (this->height)-1; row++)
    {
        for(int column = 1; column < (this->width)-1; column++)
        {   
            if (boundaryPixelMatrix[row][column] == 1)
            {
                /*
                 *  |a2 a3 a4|
                 *  |a1 ** a5|
                 *  |a8 a7 a6|
                 */
                
                int a1,a2,a3,a4,a5,a6,a7,a8;
                
                a1 = boundaryPixelMatrix[row][column-1];
                a3 = boundaryPixelMatrix[row-1][column];
                a5 = boundaryPixelMatrix[row][column+1];
                a7 = boundaryPixelMatrix[row+1][column];
                
                a2 = boundaryPixelMatrix[row-1][column-1];
                a4 = boundaryPixelMatrix[row-1][column+1];
                a6 = boundaryPixelMatrix[row+1][column+1];
                a8 = boundaryPixelMatrix[row+1][column-1];
                
                int tmpPointSum = 0;
                
                if( (a1 > 2) || (a2 > 2) || (a3 > 2) || (a4 > 2) || (a5 > 2) || (a6 > 2) || (a7 > 2) || (a8 > 2) )
                {
                    if (a1 > 0) tmpPointSum++;
                    if (a3 > 0) tmpPointSum++;
                    if (a5 > 0) tmpPointSum++;
                    if (a7 > 0) tmpPointSum++;
                    if (tmpPointSum > 2) 
                    { 
                        boundaryPixelMatrix[row][column] = 0;
                        reconfedImageMatrix[row][column] = 0;
                    } 
                    else if (tmpPointSum == 2) 
                    {
                        int removable = 0;
                        if( (a1 == 0) & (a2 == 0) & (a3 == 0) ) {
                            removable = 1;
                        } else if( (a1 == 0) & (a8 == 0) & (a7 == 0) ){
                            removable = 1;
                        } else if( (a3 == 0) & (a4 == 0) & (a5 == 0) ){
                            removable = 1;
                        } else if( (a5 == 0) & (a6 == 0) & (a7 == 0) ){
                            removable = 1;
                        }
                        
                        if (removable == 1)
                        {
                            boundaryPixelMatrix[row][column] = 0;
                            reconfedImageMatrix[row][column] = 0;
                        }    
                    }     
                }
            }    
        } 
        //std::cout<<"\n";
    }   
    return 0;
}

int Skeletonize::removeBoundaryPixelsPhase2(){
    
    for(int row = 1; row < (this->height)-1; row++)
    {
        for(int column = 1; column < (this->width)-1; column++)
        {   
            /*
             *  |a2 a3 a4|
             *  |a1 ** a5|
             *  |a8 a7 a6|
             */

            int a1,a2,a3,a4,a5,a6,a7,a8;

            a1 = boundaryPixelMatrix[row][column-1];
            a3 = boundaryPixelMatrix[row-1][column];
            a5 = boundaryPixelMatrix[row][column+1];
            a7 = boundaryPixelMatrix[row+1][column];

            a2 = boundaryPixelMatrix[row-1][column-1];
            a4 = boundaryPixelMatrix[row-1][column+1];
            a6 = boundaryPixelMatrix[row+1][column+1];
            a8 = boundaryPixelMatrix[row+1][column-1];

            int tmpPointSum = 0;

            if( (a1 > 2) || (a2 > 2) || (a3 > 2) || (a4 > 2) || (a5 > 2) || (a6 > 2) || (a7 > 2) || (a8 > 2) )
            {
                if (a1 > 0) tmpPointSum++;
                if (a3 > 0) tmpPointSum++;
                if (a5 > 0) tmpPointSum++;
                if (a7 > 0) tmpPointSum++;
                if (tmpPointSum > 2)
                {
                    boundaryPixelMatrix[row][column] = 0;
                    reconfedImageMatrix[row][column] = 0;
                } 
                else if (tmpPointSum == 2) 
                {
                    int removable = 0;
                    if( (a1 == 0) & (a2 == 0) & (a3 == 0) ) {
                        removable = 1;
                    } else if( (a1 == 0) & (a8 == 0) & (a7 == 0) ){
                        removable = 1;
                    } else if( (a3 == 0) & (a4 == 0) & (a5 == 0) ){
                        removable = 1;
                    } else if( (a5 == 0) & (a6 == 0) & (a7 == 0) ){
                        removable = 1;
                    }

                    if (removable == 1)
                    {
                        boundaryPixelMatrix[row][column] = 0;
                        reconfedImageMatrix[row][column] = 0;
                    }    
                }
            }  
        } 
        //std::cout<<"\n";
    }   
    return 0;
}


int Skeletonize::writeImage(std::string path){

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
            Magick::ColorGray gColor(this->reconfedImageMatrix[j][i]);
            Magick::PixelPacket *pixel = pixel_cache+j*columns+i;    
            *pixel = gColor;
        } 
    }
    image.syncPixels();
    image.write(path);
    
    return 0; 
}

int Skeletonize::printReconfedMatrix(){
    
    std::cout<<"Reconfigured Matrix: \n";
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->reconfedImageMatrix[row][column]<<" ";
        } 
        std::cout<<"\n";
    }   
    std::cout<<"\n\n\n\n";
    return 0;
}

int Skeletonize::printBoundaryPixelMatrix(){
    
    std::cout<<"Boundary Pixel Matrix: \n";
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->boundaryPixelMatrix[row][column]<<" ";
        } 
        std::cout<<"\n";
    }   
    std::cout<<"\n\n\n\n";
    return 0;
}