#include "Graphics.h"

#include <stdio.h>
#include <sstream>


Graphics::Graphics()
    : OurShaderManager(nullptr)
{
    OurShaderManager = new ShaderManager();
}


Graphics::~Graphics() {
    if(OurShaderManager)
        delete OurShaderManager;
    glfwTerminate();
}


// Set up the OpenGL
void
Graphics::init_ogl() {
    if(!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode* pMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    state.width  = pMode->width;
    state.height = pMode->height;
    state.nativewindow = glfwCreateWindow(state.width,
                                          state.height,
                                          "Tutorial",
                                          nullptr,
                                          nullptr
                         );
    if(state.nativewindow == nullptr) {
        printf("Failed to open GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(state.nativewindow);

// Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

// glewInit() will generate a GL_INVALID_ENUM error if used with a core profile context.
// It calls glGetString(GL_EXTENSIONS) to get the extension list, but this will generate
// GL_INVALID_ENUM with the core profile, where glGetStringi() must be used instead.
    while(true) {
        if(glGetError() == GL_NO_ERROR)
            break;
    }

// Ensure we can capture the escape key being pressed below
    glfwSetInputMode(state.nativewindow, GLFW_STICKY_KEYS, GL_TRUE);
// Hide the mouse and enable unlimited mouvement
    //glfwSetInputMode(state.nativewindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(state.nativewindow, state.width/2, state.height);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Setup the viewport
    glViewport(0, 0, state.width, state.height);
}


int
Graphics::Init(ObjectModel* TheModel) {
    return (TheModel != nullptr);
}




