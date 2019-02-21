#include "Camera.h"
#include "ObjectModel.h"


// create a God camera with some basic details
Camera::Camera(float screenRatio) {
// Projection matrix:
// 45° Field of View, "screenRatio" ratio,
// display range: near 0.1 units <->  far 14000 units
    Ratio     = screenRatio;
    FOV       = 45.0f;
	NearPlane = 0.1f;
    FarPlane  = 1400.0f;
    Target    = glm::vec3(0.0f, 0.0f, 0.0f);
    UpVector  = glm::vec3(0.0f, 1.0f, 0.0f);
		
    Projection = glm::perspective(FOV,
                                  Ratio,
                                  NearPlane,
                                  FarPlane);

    CameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
    View = glm::lookAt(CameraPos,// Camera is at CameraPos, in World Space
                       Target,   // looking at the origin and
                       UpVector);// pointing up. (0,-1, 0) will be upside-down;
}


Camera::~Camera() {
}


glm::mat4*
Camera::GetView() {
    return &View;
}



glm::mat4*
Camera::GetProjection() {
    return &Projection;
}


void
Camera::Update() {
// a simpler update just works out the new lookAt based on your position
// THIS SHOULD ALWAYS BE OVERRIDDEN
    View  = glm::lookAt(CameraPos,// Camera is at cameraPos, in World Space
                        Target,   // look at the origin
                        UpVector);// pointing up. (0,-1, 0) will be upside-down
}
	

//Camera's are objects to so they need to be moved
void
Camera::Update(ObjectModel* Controller) {
// we are taking our camera view point from a player controlled object
    glm::vec3 playerPos = Controller->GetPositon();
// provide some default systems but ideally use an overridden method
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    View = glm::lookAt(CameraPos, playerPos, Up);
}
