#pragma once

#include <iostream> // we're going to be loading files so need these
#include <fstream>
#include <string>
using namespace std;

class MyFiles
{
public:
    MyFiles();
    ~MyFiles();

public:
    int comp; // dictates what format the file is, 3 for RGB, 4 for RGBA
    char* Load(char const *filename, int*, int*); // specifically for graphics
    const char* LoadText(char const *filename);
};

