/* 
 * File:   Canny.cpp
 * Author: heshan
 * 
 * Created on April 14, 2017, 11:36 PM
 */

#include <iostream>
#include <cmath>
#include <Magick++.h>
#include "Canny.h"

Canny::Canny() {}

Canny::Canny(const Canny& orig) {}

Canny::~Canny() {}

int Canny::detectLines(std::string inputImage, std::string outputImage, int smoothType){
    initializeImage(inputImage);
    switch (smoothType)
    {
        case 1:
            gaussianFilter();
            break;
        case 2:
            meanFilter();
            break;
        default:
            break;
    }
    //printResultMatrix();
    gradients();
    //printGxMatrix();
    //printGyMatrix();
    NonMaximizedSuppression();
    gradientOrientation();
    threshold();
    writeImage(outputImage);
}

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
        this->resultMatrix = new float*[h];for(int i = 0; i < h; ++i) this->resultMatrix[i] = new float[w];
        this->gYMatrix = new float*[h];for(int i = 0; i < h; ++i) this->gYMatrix[i] = new float[w];
        this->gXMatrix = new float*[h];for(int i = 0; i < h; ++i) this->gXMatrix[i] = new float[w];
        this->gradientMagnitudeMatrix = new float*[h];for(int i = 0; i < h; ++i) this->gradientMagnitudeMatrix[i] = new float[w];
        this->gradientOrientationMatrix = new float*[h];for(int i = 0; i < h; ++i) this->gradientOrientationMatrix[i] = new float[w];
        this->NonMaximizedSuppressionMatrix = new float*[h];for(int i = 0; i < h; ++i) this->NonMaximizedSuppressionMatrix[i] = new float[w];
        this->thinnedMatrix = new float*[h];for(int i = 0; i < h; ++i) this->thinnedMatrix[i] = new float[w];
        
        // storing meta data
        this->width = w; this->height = h;
        this->range = range;
        
        float pVal = 0;
        for(row = 0; row < h; row++)
        {
            for(column = 0; column < w; column++)
            {
                Magick::Color color = pixels[w * row + column];
                pVal = (color.redQuantum()/range)/256;
                this->imageMatrix[row][column] = pVal;
                this->resultMatrix[row][column] = pVal;
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
     *          | 1 1 1 |
     *      1/9 | 1 1 1 |
     *          | 1 1 1 |
     *          
     **/ 
    
    float kernel[3][3] =    {   
                                { 1, 1, 1 },
                                { 1, 1, 1 },
                                { 1, 1, 1 }
                            };
    
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum = 0;
            if ( (row >= (this->height)-3) || (column >= (this->width)-3) ){
            
                this->resultMatrix[row][column] = this->imageMatrix[row][column];
                
            } else {
                
                
                for(int kernelRow = 0; kernelRow < 3; kernelRow++)
                {
                    for(int kernelColumn = 0; kernelColumn < 3; kernelColumn++)
                    {
                        pSum += (float)(this->imageMatrix[row + kernelRow][column + kernelColumn]*kernel[kernelRow][kernelColumn]);
                    } 
                }
                this->resultMatrix[row][column] = ( pSum/9 );
            } 
        } 
    } 
    return 0;
}

int Canny::gradients(){

    
    /**
     *     Gx= | -1  1 |
     *         | -1  1 |
     * 
     *     Gy= |  1  1 |
     *         | -1 -1 |
     * 
     **/ 
    
    float Gx[2][2] =    {   
                            { -1, 1 },
                            { -1, 1 },
                        };
    
    float Gy[2][2] =    {   
                            {  1,  1 },
                            { -1, -1 },
                        };
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum1 = 0, pSum2 = 0;
            if ( (row >= (this->height)-2) || (column >= (this->width)-2) ){
            
                this->gXMatrix[row][column] = this->imageMatrix[row][column];
                this->gYMatrix[row][column] = this->imageMatrix[row][column];
            
            } else {
                
                for(int kernelRow = 0; kernelRow < 2; kernelRow++)
                {
                    for(int kernelColumn = 0; kernelColumn < 2; kernelColumn++)
                    {
                        pSum1 += (float)(this->resultMatrix[row + kernelRow][column + kernelColumn]*Gx[kernelRow][kernelColumn]);
                        pSum2 += (float)(this->resultMatrix[row + kernelRow][column + kernelColumn]*Gy[kernelRow][kernelColumn]);
                    } 
                }
                //std::cout<<( pSum1+pSum2 )/2<<" ";
                this->gXMatrix[row][column] = pSum1;
                this->gYMatrix[row][column] = pSum2;
            }        
        } 
    }
   
    float gX,gY;
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum1 = 0, pSum2 = 0;
            if ( (row >= (this->height)-2) || (column >= (this->width)-2) ){
            
                this->resultMatrix[row][column] = this->imageMatrix[row][column];
            
            } else {
                
                gX = this->gXMatrix[row][column];
                gY = this->gYMatrix[row][column];
                
                gradientMagnitudeMatrix[row][column] = pow( (pow(gX,2)+pow(gY,2)),0.5 ); 
                //gradientOrientationMatrix[row][column] = arcTan(gX,gY);
            }        
        } 
    }
    return 0;
}

float Canny::arcTan(float x, float y){
    
    float result;
    int i = 1;
    result = -i * ( log(x + i * y)-log( pow( (pow(x,2) + pow(y,2)), 0.5 ) ) );
    return result;
}

int Canny::NonMaximizedSuppression(){

    float localMax;
    int xPos = 0,yPos = 0;
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            float pSum = 0;
            if ( (row >= (this->height)-3) || (column >= (this->width)-3) ){
            
                this->NonMaximizedSuppressionMatrix[row][column] = 0;//this->imageMatrix[row][column];
            
            } else {
                
                xPos = 0;
                yPos = 0;
                for(int kernelRow = 0; kernelRow < 3; kernelRow++)
                {
                    for(int kernelColumn = 0; kernelColumn < 3; kernelColumn++)
                    {
                        if (this->gradientMagnitudeMatrix[row + kernelRow][column + kernelColumn] > localMax) { 
                            localMax = this->gradientMagnitudeMatrix[row + kernelRow][column + kernelColumn];
                            xPos = kernelRow; yPos = kernelColumn;
                        }
                    } 
                }
                
                if ( (xPos == 0)&(yPos == 0)) {
                    this->NonMaximizedSuppressionMatrix[row][column] = gradientMagnitudeMatrix[row][column];
                    
                }
                else this->NonMaximizedSuppressionMatrix[row][column] = 0;
                //std::cout<<NonMaximizedSuppressionMatrix[row][column];
            } 
        } 
    } 
    return 0;
}

int Canny::gradientOrientation(){

    float left,right,top,bottom,curr;
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            if ( (row == 0)|| (column == 0) || (row == (this->height)-1) || (column == (this->width)-1) ){
            
                thinnedMatrix[row][column] = this->NonMaximizedSuppressionMatrix[row][column];
            
            } else {
                
                left = NonMaximizedSuppressionMatrix[row][column-1];
                right = NonMaximizedSuppressionMatrix[row][column+1];
                
                top = NonMaximizedSuppressionMatrix[row-1][column];
                bottom = NonMaximizedSuppressionMatrix[row+1][column];
                
                curr = NonMaximizedSuppressionMatrix[row][column];
                
                if ( (( left > curr ) || ( right > curr )) && ( ( top > curr ) || ( bottom > curr ) )) { 
                    thinnedMatrix[row][column] = 0; 
                } else { 
                    thinnedMatrix[row][column] = NonMaximizedSuppressionMatrix[row][column]; 
                }
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
            pVal = this->thinnedMatrix[row][column];
            //std::cout<<pVal<<"\n";
            if (pVal < 0.05) pVal = 0; else pVal = 1;
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

int Canny::writeIntermediateImage(std::string path){

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
            float pVal = this->thinnedMatrix[j][i];
            Magick::ColorGray gColor(pVal);
            Magick::PixelPacket *pixel = pixel_cache+j*columns+i;    
            *pixel = gColor;
        } 
    }
    image.syncPixels();
    image.write(path);
    
    return 0; 
}

int Canny::writeGrayScaleImage(std::string path){

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
            float pVal = this->imageMatrix[j][i];
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
    std::cout<<"\n\n\n\n";
    return 0;  
}

int Canny::printGxMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->gXMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }  
    std::cout<<"\n\n\n\n";
    return 0;  
}

int Canny::printGyMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->gYMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }  
    std::cout<<"\n\n\n\n";
    return 0;  
}

int Canny::printGmMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->gYMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }  
    std::cout<<"\n\n\n\n";
    return 0;  
}

int Canny::printGoMatrix(){
    
    for(int row = 0; row < (this->height); row++)
    {
        for(int column = 0; column < (this->width); column++)
        {
            std::cout<<this->gYMatrix[row][column]<<" ";
        } 
        std::cout<< std::endl;
    }  
    std::cout<<"\n\n\n\n";
    return 0;  
}
