TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ../Headers
INCLUDEPATH += ../../external/glfw-3.1.2/include/
INCLUDEPATH += ../../external/glm-0.9.9.3/
INCLUDEPATH += ../../external/glew-1.13.0/include
INCLUDEPATH += ../../external/stb/
INCLUDEPATH += /usr/include/bullet


LIBS += -L/usr/lib
LIBS += -L../../build/external
LIBS += -L../../build/external/glfw-3.1.2/src


LIBS += -lglfw3
LIBS += -lX11
LIBS += -lGLEW_1130
LIBS += -lpthread
LIBS += -lGL
LIBS += -ldl
LIBS += -lXxf86vm
LIBS += -lXrandr
LIBS += -lXinerama
LIBS += -lXcursor
LIBS += -lXi
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath


SOURCES += \
        main.cpp \
    Camera.cpp \
    Game.cpp \
    Graphics.cpp \
    ModelManager.cpp \
    ObjectModel.cpp \
    ShaderManager.cpp \
    TextureManager.cpp \
    MyFiles.cpp \
    CubeModel.cpp

HEADERS += \
    Camera.h \
    Game.h \
    Graphics.h \
    ObjectModel.h \
    ShaderManager.h \
    stb_image.h \
    TextureManager.h \
    MyFiles.h \
    ModelManager.h \
    CubeModel.h

DISTFILES += \
    vertexshader.vert \
    fragmentshader.frag \
    Harvey2.jpg
