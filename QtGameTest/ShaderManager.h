#pragma once

#include <GL/glew.h>
#include <vector>
#include "MyFiles.h"


//most standard OGL dems use int versions of TRUE and FALSE (careful not to mix up with bool true and false)
#define TRUE 1
#define FALSE 0

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

public:
    // Not used
    //    void   LoadAll();  // an init routine to load all shaders and store them
    GLuint MakeShader(GLenum type, const char* ShaderArray); //compile a shader from an array as before
    GLuint LoadAndMakeShader(MyFiles*, GLenum type, const char* Fname); // same idea but load from a file

    GLuint MakeProgramObject(GLuint VShad, GLuint FShad);
    GLuint MakeProgramObject(const char* Vfname, const char* Ffname, MyFiles* FH); // more likely to use this one

    std::vector<GLuint> FShaders;
    std::vector<GLuint> VShaders;
    std::vector<GLuint> ProgramObjects;
};
