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
    Skeletonize();
    Skeletonize(const Skeletonize& orig);
    virtual ~Skeletonize();
    
    int initializeImage(std::string path);
    int reconfPixels();
    int getArticulationPoints();
    
    int printReconfedMatrix();
    int printResultMatrix();
    
private:
    Magick::Image img;
    float **imageMatrix,**reconfedImageMatrix,**resultMatrix;
    int width, height;
    double range;

};

#endif /* SKELETONIZE_H */

