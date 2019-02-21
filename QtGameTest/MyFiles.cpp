#include "MyFiles.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


MyFiles::MyFiles() {
}


MyFiles::~MyFiles() {
}


char*
MyFiles::Load(char const *filename, int* width, int* height) {
    unsigned char *data = stbi_load(filename, width, height, &comp, 4); // ask it to load 4 componants since its rgba
    if(*width**height==0) {
        printf("Texture failed to load at path: %s\n",
               filename);
        stbi_image_free(data);
        exit(EXIT_FAILURE);
    }
    printf("Loaded texture : %s\n", filename);
    return reinterpret_cast<char*>(data);
}


// will load a standard style text file used by shaders
const char*
MyFiles::LoadText(char const *filename) {
    static string line; // we are returning this, so it needs to stay in scope
    // hence make it static so it exists when the routine is done, a local variable will be unpredictable
    ifstream myfile(filename);
    if(myfile.is_open()) {
        getline(myfile, line, char(myfile.eof())); // *this.eof isn't ideal but it works
        myfile.close();
    }
    else {
        printf("Unable to load file- check filename %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return line.c_str();
}
