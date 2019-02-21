#pragma once

// Somewhere to load and keep track of our textures, since it is not desirable to have
// multiple loads of the same texture, a map will be used to check if the file is already in place
// All texture loads will come here, and test if the texture is already in place in texture memory

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>


#include "MyFiles.h"
#include "ShaderManager.h"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

public:
    // create with and without a graphic filehandler
    GLuint LoadandCreateTexture(const char *fname, MyFiles* FH);  //returns the id of the texture
    GLuint LoadandCreateTexture(const char *fname); //returns the id of the texture
    //textures need to be deleted here
    bool deleteTexture(GLuint IDofTexture); // removes from Texture space by ID, and from the map, return false if not possible
    bool deleteTexture(char* FileNameOfTexture); // removes from Texture space by name, and from the map

public:
    // Manager will keep a record of the textures used to avoid reloading
    std::map<std::string, GLuint> Totaltextures;
};
