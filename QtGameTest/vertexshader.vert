#version 330 core

layout(location = 0) in vec3 vertexModelPosition;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 MVP;

out vec2 v_texCoord;

void main(){
    gl_Position = MVP * vec4(vertexModelPosition,1);
    v_texCoord  = a_texCoord;
}
