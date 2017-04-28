# Line Detection
line detection of images.

## Skeletonization
process of reducing foreground regions in a binary image.

![sourceImg](https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/lines.gif) 
![arrow](https://github.com/heshanera/lineDetection/blob/master/imgs/arw.png)
![skeletonizedImg](https://github.com/heshanera/lineDetection/blob/master/imgs/skdtest1.png)

## Convolution
applying the kernels to the skeletonized image to detect the lines.

#### Kernels
![kernels](https://github.com/heshanera/lineDetection/blob/master/imgs/kernels.png)

##### Applying the 4 kernels
![kernel1](https://github.com/heshanera/lineDetection/blob/master/imgs/result1.png) 
![kernel2](https://github.com/heshanera/lineDetection/blob/master/imgs/result2.png)
![kernel3](https://github.com/heshanera/lineDetection/blob/master/imgs/result3.png)
![kernel4](https://github.com/heshanera/lineDetection/blob/master/imgs/result4.png) 

## Canny Operator
![sourceImg](https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i1.gif)
![intermediateImg](https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut1.png) 
![outputImage](https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut1.png)

<img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i1.gif" alt="src" width="200">
<img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut1.png" alt="intm" width="200">
<img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut1.png" alt="out" width="200">
