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

<table>
<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i7.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut7.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut7.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i1.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut1.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut1.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i2.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut2.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut2.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i3.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut3.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut3.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i4.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut4.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut4.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i5.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut5.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut5.png" alt="out">
</td>
</tr>

<tr>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/i6.gif" alt="src" >
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyIntOut6.png" alt="intm">
</td>
<td>
 <img src="https://github.com/heshanera/lineDetection/blob/master/imgs/cannyOut6.png" alt="out">
</td>
</tr>

</table>
