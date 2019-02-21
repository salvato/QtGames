
#pragma once

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <algorithm>


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <vector>
// Include GLM
#undef countof
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#undef countof

#include "Graphics.h"
#include "MyFiles.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"


class Camera;
class ObjectModel;


// these are the minimum contents of a game class
class Game
{
public:
	Game();
	~Game();
	
	Graphics* MyGraphics; // create a 1 time instance of a graphics class;
	
    MyFiles	FileHandler;
	std::vector<ObjectModel*> MyObjects;

	Camera*	TheCamera;
    Camera* GetCamera() {
		return TheCamera;
	}
	
    uint32_t ScreenX, ScreenY;
	ModelManager MainModelManager; // all models are loaded and info stored here this managter is passed to objects created
    bool Init();
    bool Update(float deltaTime);
    void Draw(Graphics::Target_State *p_state);
	
	float DeltaTimePassed; 
		
protected:
};




