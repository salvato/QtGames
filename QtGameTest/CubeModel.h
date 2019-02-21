#pragma once

#include "ObjectModel.h"

// a very simple hard cube model, it only needs to do a few things
// because it inherets ObjectModel, all the meaty data is in there

class CubeModel : public ObjectModel
{
public:
	CubeModel();
    virtual ~CubeModel();

public:
    CubeModel(MyFiles* FH); // a new kind of contructor
    bool Update() ;         // we supply an update
    bool Draw();            // and a draw
	bool Init();

public:
    GLuint Shader;
    GLint MatrixID;
};
