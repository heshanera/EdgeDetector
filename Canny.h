/* 
 * File:   Canny.h
 * Author: heshan
 *
 * Created on April 14, 2017, 11:36 PM
 */

#ifndef CANNY_H
#define CANNY_H

#include <iostream>
#include <Magick++.h>

class Canny {
public:
    Canny(std::string inputImage, std::string outputImage, int smoothType);
    Canny(const Canny& orig);
    virtual ~Canny();
    
    int initializeImage(std::string path);
    int grayScale();
    int gaussianFilter();
    int meanFilter();
    int gradients();
    float arcTan(float x, float y);
    int NonMaximizedSuppression();
    int gradientOrientation();
    int threshold();
    int writeImage(std::string path);
    
    int printResultMatrix();
    int printGxMatrix();
    int printGyMatrix();
    int printGmMatrix();
    int printGoMatrix();
    
private:
    Magick::Image img;
    float   **imageMatrix,**resultMatrix,
            **gXMatrix,**gYMatrix,
            **gradientMagnitudeMatrix,**gradientOrientationMatrix,
            **NonMaximizedSuppressionMatrix, **thinnedMatrix;
    int width, height;
    double range;

};

#endif /* CANNY_H */

