#pragma once

#include <GL/glew.h>   // OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source
                       // C/C++ extension loading library. http://glew.sourceforge.net/

#include <GLFW/glfw3.h>// GLFW is a free, Open Source, multi-platform library for OpenGL,
                       // OpenGL ES and Vulkan application development. https://www.glfw.org
                       // It provides a simple, platform-independent API for creating windows,
                       // contexts and surfaces, reading input, handling events, etc.

#include <glm/glm.hpp> // OpenGL Mathematics (glm.g-truc.net)
using namespace glm;
#include <vector>
#include "ObjectModel.h"

// this is just for fun, the CPU can't hold such a big number but does not mind you trying to define it.
#define PI         3.14159265358979323846264338327950288419716939937510582097494459072381640628620899862803482534211706798f
#define DEG2RAD(x) (x*PI)/180
#define RAD2DEG(x) x*(180/PI)


//most standard OGL demos use int versions of TRUE and FALSE (careful not to mix up with bool true and false)
#define TRUE 1
#define FALSE 0


class Graphics 
{
public:
	Graphics();
	~Graphics();
	
public:
    typedef struct {
        GLuint programObject;// save a Handle to a program object
        GLint  positionLoc;  // Attribute locations
        GLint  texCoordLoc;
        GLint  samplerLoc;   // Sampler location
        GLuint textureId;    // Texture handle
    } ObjectData;

    typedef struct Target_State {
        int32_t width;
        int32_t height;
        GLFWwindow* nativewindow;
        GLuint programObject;
        ObjectData *object_data;
        void(*draw_func)(struct Target_State*);
    } Target_State;

    Target_State state;
	Target_State* p_state = &state;
		
    void init_ogl();

    int Init(ObjectModel* TheModel);

    ShaderManager* OurShaderManager;
};
