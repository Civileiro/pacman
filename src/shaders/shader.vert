#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;
out vec3 fragPos;


uniform mat4 model;

void main()
{
    texCoords = aTexCoords;
    vec4 vertPos = vec4(aPos, 1.f);
    fragPos = vec3(model * vertPos);

    gl_Position = model * vertPos;
}