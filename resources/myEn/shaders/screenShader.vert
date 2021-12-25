#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 texTransform;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vec2(texTransform * vec4(aTexCoords, 0.f, 1.f));

    
    gl_Position = projection * model * vec4(aPos, 0.f,  1.f);
    //gl_Position = vec4(aPos, 0.f,  1.f);

}