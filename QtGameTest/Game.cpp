//=========================================================
// This is the Game class, our project should run from here
//=========================================================
#include "Game.h"
#include "Camera.h"
#include "ObjectModel.h"
#include "CubeModel.h"


// Don't do anything special here, leave it to the init.
// But do set up the OpenGL window stuff.
Game::Game() {
    MyGraphics = new Graphics(); // Will also create a ShaderManager
    MyGraphics->init_ogl();      // Set our display window to screen size
}


Game::~Game() {
    for(uint i=0; i<MyObjects.size(); i++) {
        delete MyObjects[i];
    }
    MyObjects.clear();
    delete TheCamera;
    delete MyGraphics;
}


// Set up the Game stuff
bool
Game::Init() {
//=================================
// Create a Camera
//=================================
    float ratio = MyGraphics->state.width/MyGraphics->state.height;
    TheCamera = new Camera(ratio);
    CubeModel* T = new CubeModel(&FileHandler);
    glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0);
    T->StoreGraphicClass(MyGraphics);
    T->SetPosition(Pos);
    T->TheGame = this;
// Create and compile our GLSL program from the shaders
    GLuint programObject = MyGraphics->
                           OurShaderManager->
                           MakeProgramObject("vertexshader.vert",
                                             "fragmentshader.frag",
                                             &FileHandler);
    T->programObject  = programObject;
    T->TheGraphics = MyGraphics;
    T->Init(); // set up all GPU variables as a one time thing
    Game::MyObjects.push_back(T);
    return true;
}


bool
Game::Update(float deltaTime) {
// Give ojects access to the passage of time
    DeltaTimePassed = deltaTime;

// Get ready to cycle through any objects we made
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(ulong i=0; i<MyObjects.size(); i++) {
        MyObjects[i]->Update();
        MyObjects[i]->Draw();
    }// for(ulong i=0; i<MyObjects.size(); i++)

// After our draw we need to swap buffers to display
    glfwSwapBuffers(MyGraphics->p_state->nativewindow);
    glfwPollEvents();
    if((glfwGetKey(MyGraphics->state.nativewindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) ||
       (glfwWindowShouldClose(MyGraphics->state.nativewindow) != 0)) {
        return false;
    }
    return true;
}
