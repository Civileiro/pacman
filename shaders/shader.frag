#version 330 core
out vec4 fragColor;

in vec2 TexCoords;
flat in int TexID;

uniform sampler2D textures[2];

void main()
{    
    
    fragColor = texture(textures[TexID], TexCoords);
    //fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}