# Line Detection
line detection of images.

## Skeletonization
process of reducing foreground regions in a binary image.
<table>
<tr>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/inputImages/lines.gif" alt="" > </td>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/arw.png" alt="" > </td>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/skdtest1.png" alt="" > </td>
</tr>
</table>

## Convolution
applying the kernels to the skeletonized image to detect the lines.

#### Kernels
![kernels](https://github.com/heshanera/lineDetection/blob/master/imgs/kernels.png)

##### Applying the 4 kernels
<table>
<tr>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/result1.png" alt="kernel1" > </td>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/result2.png" alt="kernel2" > </td>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/result3.png" alt="kernel3" > </td>
<td><img src="https://github.com/heshanera/lineDetection/blob/master/imgs/result4.png" alt="kernel4" > </td>
</tr>
</table>

## Canny Operator

<table>

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

</table>
