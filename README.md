# ray-tracing
source code are in hw1 folder

compiled using visual studio 2015, should be able to run on any windows version newer than xp.

all the source code are under hw1 folder, can be compiled using g++
no platform related dependency

#result
results are under hw1/Results/ folder

#pre-compiled program

hw1d under hw1 folder

#compile
##ubuntu
under hw1 folder:
```
g++-5 -std=c++11 *.cpp -o hw1d
```

##windows
open hw1.sln using visual studio and compile

##mac
clang++ -std=c++11 -stdlib=libc++11 *.cpp -o hw1d

#use
under hw1 folder:
```
./hw1d TestFiles/input1.txt Results/out1.ppm
./hw1d TestFiles/input2.txt Results/out2.ppm
./hw1d TestFiles/input3.txt Results/out3.ppm
```
