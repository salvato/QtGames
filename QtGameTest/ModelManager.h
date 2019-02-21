#pragma once

#include	<map>
#include	<string>
#include	<vector>
#include <GL/glew.h>
#undef countof
#include	"glm/glm.hpp"
#include	"glm/gtc/matrix_transform.hpp"
#undef countof
#include	"ObjectModel.h"
#include	"MyFiles.h"
#include	"ShaderManager.h"
#include	"TextureManager.h"

typedef struct { // otherwise this is a temp and probably unused concept but some functions set defaults
    float x;
    float y;
    float z;
} btVector3;


class ModelManager
{
public:
    ModelManager();
    ~ModelManager();

public:
// Texture manager will keep hold of the textures
    TextureManager TexManager;
private:
}; // class



