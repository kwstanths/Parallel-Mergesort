# Parallel-Mergesort
An implementation of a parallel mergesort

#Build the library 
mkdir build/release

cd build/release

cmake ../../

make

sudo make install

#Build bin
Change main CMakeLists.txt file to include bin directory

cd build/release

cmake ../../

make

#Use the library
Add FindmyPMSort.cmake file to your CMake Module path,
See bin/CMakeLists.txt to use in your CMake project
