#include "CubeModel.h"
#include "Graphics.h"
#include "Camera.h"
#include "Game.h"


static GLfloat CubeVertices[] = { // it's a cube model so it needs to know what a cube looks like
                                  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                                   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                                   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                                   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                                  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                                  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                                  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                                   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                                   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                                   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                                  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                                  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                                  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                                  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                                  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                                  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                                  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                                  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                                   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                                   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                                   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                                   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                                   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                                   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                                  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                                   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                                   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                                   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                                  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                                  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                                  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                                   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                                   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                                   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                                  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                                  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
                                };

// Load, create texture 
CubeModel::CubeModel(MyFiles* FH) {
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    mTranslationMatrix	= glm::mat4(1.0f);
    mRotationMatrix		= glm::mat4(1.0f);
    mScaleMatrix		= glm::mat4(1.0f);
    Model	            = glm::mat4(1.0f);
    glm::vec3 Pos = glm::vec3(11.0f, 0.0f, 0.4f);
    SetPosition(Pos);

    Scales = glm::vec3(1.0f, 1.0f, 1.0f);
    SetModelMatrix();
    Vertices = CubeVertices;
    Colour = glm::vec4(Rand(1.0f), Rand(1.0f), Rand(1.0f), 1.0f);

// This cube model creates a VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat)*(36*5),
                 Vertices,
                 GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // unbind to make sure its cleared
    glBindVertexArray(0);
    int width=0, height=0;
    char* image = FH->Load(static_cast<const char*>("Harvey2.jpg"), &width, &height);
    if(width*height==0) {
        printf("Unable to load the texture\n");
        exit(EXIT_FAILURE);
    }
// Create our texture and store the handle in texture
    glGenTextures(1, &texture1);
// Bind it, so it now is what we are looking at
    glBindTexture(GL_TEXTURE_2D, texture1);
// Set our texture parameters
// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// Now put the image in there...might be tricky
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image
    );
// Unbind texture when done, so we won't accidentily mess up our texture.
    glBindTexture(GL_TEXTURE_2D, 0);
}


CubeModel::CubeModel() {
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    mTranslationMatrix	= glm::mat4(1.0f);
    mRotationMatrix		= glm::mat4(1.0f);
    mScaleMatrix		= glm::mat4(1.0f);
    Model	            = glm::mat4(1.0f);
    glm::vec3 Pos = glm::vec3(11.0f, 0.0f, 0.4f);
    SetPosition(Pos);

    Scales = glm::vec3(1.0f, 1.0f, 1.0f);
    SetModelMatrix();
    Vertices = CubeVertices;
    Colour = glm::vec4(Rand(1.0f), Rand(1.0f), Rand(1.0f), 1.0f);

/********************************************************************
 Lets make a VBO to store these vertices in GPU memory, we could give
 each cube its own VBO, but they are all the same data, so we'll cheat
 a bit from how the book describes it and use a single static value
 which we will feed to each instance of a cube so they all use the same
 VBO handle, as long as they are all cubes this is fine.
*******************************************************************/

// This cube model creates a VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat)*(36*5),
                 Vertices,
                 GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


CubeModel::~CubeModel() {
}


// we've added an init, who's main function is to make sure that we reduce the number of  calls to GPU functions especially location searches
// this has to be called when you create the Cube (currently back in HelloCubes as part of the setup)
bool
CubeModel::Init() {
    positionLoc = glGetAttribLocation(programObject, "vertexModelPosition");
    texCoordLoc = glGetAttribLocation(programObject, "a_texCoord");
    MatrixID    = glGetUniformLocation(programObject, "MVP");
    return true;
}




bool
CubeModel::Update() {
    //	Init(); // its only finding a few values, but it takes a long time to do it, so repeating it here is unwise.

    // if this were a cool object we might do some update and movement here... for now we'll just spin them
    DegreeRotations.x += TheGame->DeltaTimePassed;
    Rotations.x = DEG2RAD(DegreeRotations.x);

    DegreeRotations.y += TheGame->DeltaTimePassed;
    Rotations.y = DEG2RAD(DegreeRotations.y);

    DegreeRotations.z += TheGame->DeltaTimePassed;
    Rotations.z = DEG2RAD(DegreeRotations.z);
// once we've made some change to their data, we should update the matrices that will be affected
// but here we'll just do them all.
    MakeRotationMatrix();
    MakeTranslationMatrix();
    MakeModelMatrix();

// get the projection and view from the static camera held in graphics
    glm::mat4* Projection = TheGame->TheCamera->GetProjection();
    glm::mat4* View       = TheGame->TheCamera->GetView();
    glm::mat4  MVP        = (*Projection) * (*View) * Model;

    glUseProgram(programObject); // bind our shader so we can send things to it
// send our MVP to the matrix
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
// all done, return true, for now, we have no failure conditions to return
    return true;
}


// the update method positioned and rotated it, time to draw it.
// this new draw system is now able to use the generated VBO and we have also
// avoided doing uniform and attribute handle generators, since they will never change
// and asking the gpu for that is very slow. They are one once with an Init() call when the cube
// is created. All these little changes make for a huge increase in speed.
bool
CubeModel::Draw() {
    glBindVertexArray(vertexArrayID);
    glUseProgram(programObject); // should still be the same but good to be sure

    // With VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(GLuint(positionLoc),
                          3,// 3 values
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*5,// stride
                          static_cast<void*>(nullptr)
    );

    // Without VBO	this will be around half as fast on this amount of data, with larger objects it could be many times slower
    //	glBindBuffer(GL_ARRAY_BUFFER, 0); // use no vbo and notice we use the vertices address held in Vertices
    //	glVertexAttribPointer(this->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), Vertices);   // use 3 values, but add 5 each time to get to the next

    // Load the texture coordinate
    glVertexAttribPointer(GLuint(texCoordLoc),
                          2,// 2 values
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*5,// stride does not change
                          reinterpret_cast<void*>(3*sizeof(GLfloat))
    );
    glBindTexture(GL_TEXTURE_2D, this->texture1);

    glEnableVertexAttribArray(GLuint(texCoordLoc));
    glEnableVertexAttribArray(GLuint(positionLoc)); // enable
    glDrawArrays(GL_TRIANGLES, 0, 36); // draw
    glBindVertexArray(0);

    // this is also very slow, only uncomment it if you feel you need to check if there is an error
    if (glGetError() != GL_NO_ERROR) {// check all is well
        printf("Oh bugger CubeModel Draw error\n");
        return false;
    }
    return true;
}


