/* 
 * File:   DetectLine.h
 * Author: heshan
 *
 * Created on April 10, 2017, 9:06 PM
 */

#ifndef DETECTLINE_H
#define DETECTLINE_H

#include <iostream>
#include <Magick++.h>


class DetectLine {
public:
    DetectLine();
    DetectLine(const DetectLine& orig);
    virtual ~DetectLine();
    
    int getLines(std::string inputImage, std::string outputImage, int kernelNo);
    int initializeImage(std::string path);
    int writeImage(std::string path);
    int applyKernel(int kernelNO);
    
    int printImageMatrix();
    int printResultMatrix();
    
private:
    Magick::Image img;
    float **imageMatrix,**resultMatrix;
    int width, height;
    double range;
   
};

#endif /* DETECTLINE_H */

