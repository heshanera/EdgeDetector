/* 
 * File:   Skeletonize.h
 * Author: heshan
 *
 * Created on April 11, 2017, 8:39 PM
 */

#ifndef SKELETONIZE_H
#define SKELETONIZE_H

#include <iostream>
#include <Magick++.h>

class Skeletonize {
public:
    Skeletonize(std::string inputImage, std::string outputImage);
    Skeletonize(const Skeletonize& orig);
    virtual ~Skeletonize();
    
    int initializeImage(std::string path);
    int reconfPixels();
    int getArticulationPoints();
    int removeBoundryPixels();
    
    int printReconfedMatrix();
    int printResultMatrix();
    
private:
    Magick::Image img;
    float **imageMatrix,**reconfedImageMatrix,**boundryPixelMatrix;
    int width, height;
    double range;

};

#endif /* SKELETONIZE_H */

