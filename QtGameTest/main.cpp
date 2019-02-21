#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include GLM
#undef countof
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#undef countof

#include "Game.h"
#include "Graphics.h"

//#define PRINT_GPU_INFO
#define PRINT_FRAME_TIME


void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam
)
{
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;
    printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
           type,
           severity,
           message
    );
    printf("GL CALLBACK: source = 0x%x, id = 0x%x, length = %d\n",
           source,
           id,
           length
    );
    if(userParam != nullptr)
        printf("There are also User's parameters\n");
    if(type == GL_DEBUG_TYPE_ERROR)
        exit(EXIT_FAILURE);
}


int
main() {
    Game* TheGame;
    TheGame = new Game();
    TheGame->Init();

    // Enable OpenGL asynchronous debug
    if(GLEW_ARB_debug_output) {
        glDebugMessageCallback(MessageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT);
    }

#ifdef PRINT_GPU_INFO
    // lets get some info on our GPU
    printf("This GPU supplied by :%s  \n", glGetString(GL_VENDOR));
    printf("This GPU supports :%s     \n", glGetString(GL_VERSION));
    printf("This GPU Renders with :%s \n", glGetString(GL_RENDERER));
    printf("This GPU supports :%s     \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    GLint MaxTextureUnits, MaxVertexTextureUnits, MaxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,        &MaxTextureUnits);
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &MaxVertexTextureUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,               &MaxTextureSize);

    printf("This GPU supports :%d Texture Units\n",        MaxTextureUnits);
    printf("This GPU supports :%d Vertex Texture Units\n", MaxVertexTextureUnits);
    printf("This GPU supports :%d Max Texture Size\n",     MaxTextureSize);
#endif

    struct timeval t1, t2;
    struct timezone tz;
    float deltatime;
#ifdef PRINT_FRAME_TIME
    float totaltime = 0.0f;
    unsigned int frames = 0;
#endif

    gettimeofday(&t1, &tz);
    while(true) {
        gettimeofday(&t2, &tz);
        deltatime = float(t2.tv_sec-t1.tv_sec + (t2.tv_usec-t1.tv_usec)*0.0000001f);
        t1 = t2;
// Here it is where the magic happens !
// If Update() ever returns false the Game is Over
        if(TheGame->Update(deltatime) == false) {
            break;
        }
#ifdef PRINT_FRAME_TIME
// otherwise let our user know how long that game cycle took let our user know how long that all took
        totaltime += deltatime;
        frames++;
        if(totaltime > 1.0f) {
            printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n",
                   frames,
                   double(totaltime),
                   double(frames/totaltime)
            );
            totaltime -= 1.0f;
            frames = 0;
        }
#endif
    }

    return EXIT_SUCCESS;
}

