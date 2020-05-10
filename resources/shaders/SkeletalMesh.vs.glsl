#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoords;
layout(location = 2) in vec3 inNormals;
layout(location = 3) in ivec4 inBoneIDs;
layout(location = 4) in vec4 inBoneWeights;

out vec2 fsTexCoords;
out vec3 fsPosition;
out vec3 fsNormals;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform mat4 uBones[100];

void main()
{
    mat4 boneTransform =  uBones[inBoneIDs[0]] * inBoneWeights[0];
    boneTransform += uBones[inBoneIDs[1]] * inBoneWeights[1];
    boneTransform += uBones[inBoneIDs[2]] * inBoneWeights[2];
    boneTransform += uBones[inBoneIDs[3]] * inBoneWeights[3];

    fsTexCoords = inTexCoords;
    fsPosition = vec3(uModel * (boneTransform * vec4(inPosition, 1.0)));
    //fsNormals = mat3(transpose(inverse(uModel))) * vec3(boneTransform * vec4(inNormals, 1.0));
    fsNormals = normalize(vec3(uModel * boneTransform * vec4(inNormals, 0)));

    mat4 mvp = uProj * uView * uModel;
    vec4 bonePos = boneTransform * vec4(inPosition, 1.0);
    gl_Position = mvp * bonePos;
}