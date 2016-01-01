# ray-tracing


#compile
##ubuntu
```
g++-5 -std=c++11 *.cpp -o rt
```

##mac
clang++ -std=c++11 -stdlib=libc++11 *.cpp -o rt

#use
```
./rt test_files/input1.txt results/out1.ppm
./rt test_files/input2.txt results/out2.ppm
./rt test_files/input3.txt results/out3.ppm
```
