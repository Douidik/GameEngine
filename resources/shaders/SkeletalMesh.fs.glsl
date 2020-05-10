#version 460 core

out vec4 result;

in vec2 fsTexCoords;
in vec3 fsPosition;
in vec3 fsNormals;

uniform vec3 uLightPos;
uniform vec3 uViewPos;
uniform vec3 uLightColor;

uniform float uAmbientStrength;
uniform float uSpecularStrength;

uniform sampler2D uTextureDIFFUSE0;

void main()
{
    //Base
    vec4 base = texture(uTextureDIFFUSE0, fsTexCoords);

    //Ambient
    vec3 ambient = uAmbientStrength * uLightColor;

    //Diffuse
    vec3 norm = normalize(fsNormals);
    vec3 lightDir = normalize(uLightPos - fsPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;

    //Specular
    vec3 viewDir = normalize(uViewPos - fsPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uSpecularStrength * spec * uLightColor * vec3(base);

    //Result
    result = vec4(((ambient + diffuse + specular) * vec3(base)), 1.0);
}