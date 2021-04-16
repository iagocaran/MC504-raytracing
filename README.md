# MC504-raytracing

An adaptation of threads in a C [raytracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) engine for the MC504 subject at University of Campinas (UNICAMP)

## Introduction

This project is the adaptation of my COARV-raytracing project to use threads via pthread lib.

## Getting started

### Installation

If using linux, make sure you have pthread lib. Headers, lib and dll bundled for windows.

1. Clone the repo:
```sh
git clone https://github.com/iagocaran/MC504-raytracing.git
```
2. Build with cmake
```sh
cmake .
make
```

## Usage

The project will output an image to cout and the progress to cerr, so you can just run like this to get the output:
```sh
raytracing > image.ppm
```

The output images can be previewed in a [PPM Viewer](http://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html).

## Results

In the way it is implemented, the program will spawn one thread for each width pixel, this can overload the stack for bigger images, be warned.
With that in mind, we could paralelize using the samples loop, but that would create a critical region problem. 
Another option is to subdivide the loop in multiple parts of a reasonable size as to not overload the stack.
I think we can consider the raytracing more adapted to a buffer approach, where we have on one side a thread that creates tasks to be executed by other tasks.

Here we have an image example of the output:
![Example of output](https://github.com/iagocaran/MC504-raytracing/blob/master/output.png)
With this resolution, the program took me a little more than half a day in singlethread and one hour and a half in multithreaded.

## Credits

* Peter Shirley for his [Ray Tracing in One Weekend book](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
