#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in float aTexID;

out vec2 TexCoords;
flat out int TexID;

uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    TexID = int(aTexID);

    gl_Position = projection * vec4(aPos, 0.f,  1.f);
    //gl_Position = vec4(aPos, 0.f,  1.f);

}