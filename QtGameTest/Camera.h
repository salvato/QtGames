#pragma once

// Include GLM
#undef countof
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ObjectModel;


class Camera
{
public:
    Camera(float screenRatio);
    virtual ~Camera();

public:
    glm::mat4* GetView();
    glm::mat4* GetProjection();
    virtual void Update(ObjectModel* ControllingObject);
    virtual void Update();  // updates using its own position and matrix values

public:
    glm::mat4 View; // used by MVP calculations
    glm::mat4 Projection;
    glm::vec3 CameraPos;

    float Roll; // when we move independant of an object
    float Pitch;
    float Yaw;

    float Ratio;
    float FOV;
    float NearPlane;
    float FarPlane;
    glm::vec3 Target;
    glm::vec3 UpVector;
};
