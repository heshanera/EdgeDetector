/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectLine.h
 * Author: heshan
 *
 * Created on April 10, 2017, 9:06 PM
 */

#ifndef DETECTLINE_H
#define DETECTLINE_H

#include <iostream>


class DetectLine {
public:
    DetectLine();
    DetectLine(const DetectLine& orig);
    virtual ~DetectLine();
    
    int initializeImage(std::string path,char **argv);
    int printImageMatrix();
    int writeImage(std::string path);
    
private:
    float** imageMatrix;
    int width, height;
    double range;

};

#endif /* DETECTLINE_H */

