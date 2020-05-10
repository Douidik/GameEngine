#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoords;
layout(location = 2) in vec3 inNormals;

out vec2 fsTexCoords;
out vec3 fsPosition;
out vec3 fsNormals;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    fsTexCoords = inTexCoords;
    fsPosition = vec3(uModel * vec4(inPosition, 1.0));
    fsNormals = mat3(transpose(inverse(uModel))) * inNormals;

    mat4 mvp = uProj * uView * uModel;
    gl_Position = mvp * vec4(inPosition, 1.0);
}