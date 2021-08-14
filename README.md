# ipcv


This is the readme.txt for coursework COMS30031

<Subtask 1>

compile and build face.cpp:
```
 g++ face.cpp /usr/lib64/libopencv_core.so.2.4 /usr/lib64/libopencv_highgui.so.2.4 /usr/lib64/libopencv_imgproc.so.2.4 /usr/lib64/libopencv_objdetect.so.2.4 
 ./a.out dart14.jpg 
```
this will show the resulting detection and the output image detected1.jpg (example is dart14.jpg)

<Subtask 2> 
for permission:\
```
chmod u+x opencv_createsamples
```
to create 500 images of dartboards:
```
./opencv_createsamples -img dart.bmp -vec dart.vec -w 20 -h 20 -num 500 -maxidev 80 -maxxangle 0.8 -maxyangle 0.8 - maxzangle 0.2
```
start boosting and construct a strong classifier:

```
chmod u+x opencv_traincascade
./opencv_traincascade -data dartcascade -vec dart.vec -bg negatives.dat -numPos 500 -numNeg 500 -numStages 3 -maxDepth 1 -w 20 -h 20 -minHitRate 0.999 -maxFalseAlarmRate 0.05 -mode ALL
```


then run:
```
g++ face2.cpp /usr/lib64/libopencv_core.so.2.4 /usr/lib64/libopencv_highgui.so.2.4 /usr/lib64/libopencv_imgproc.so.2.4 /usr/lib64/libopencv_objdetect.so.2.4 

./a.out dart14.jpg
```

this will show the resulting detection and the output image cascadedetected.jpg (an example is dart14.jpg)


<Subtask 3> 

houghline: 
```
g++ houghLine.cpp /usr/lib64/libopencv_core.so.2.4 /usr/lib64/libopencv_highgui.so.2.4 /usr/lib64/libopencv_imgproc.so.2.4 /usr/lib64/libopencv_objdetect.so.2.4 

./a.out dart1.jpg 
```
this will generate an output image called “houghLine.jpg” (an example is dart1.jpg)


houghcircle: 

```
g++  houghcircle.cpp /usr/lib64/libopencv_core.so.2.4 /usr/lib64/libopencv_highgui.so.2.4 /usr/lib64/libopencv_imgproc.so.2.4 /usr/lib64/libopencv_objdetect.so.2.4 
./a.out dart1.jpg
```

this will generate an output image called “houghCircle.jpg” 



