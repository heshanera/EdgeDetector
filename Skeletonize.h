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
    int getArticulationPointsPhase2();
    int removeBoundaryPixels();
    int removeBoundaryPixelsPhase2();
    int writeImage(std::string path);
    
    int printReconfedMatrix();
    int printBoundaryPixelMatrix();
    
private:
    Magick::Image img;
    float **imageMatrix,**reconfedImageMatrix,**boundaryPixelMatrix;
    int width, height;
    double range;
    int interiorPixels;

};

#endif /* SKELETONIZE_H */

