#version 460 core
out vec4 fragColor;

in vec2 TexCoords;
flat in int TexID;

uniform sampler2D textures[8];

void main()
{    
    vec4 color = texture(textures[TexID], TexCoords);
    if(color == vec4(0.f, 0.f, 0.f, 1.f)){
        discard;
    }
    fragColor = color;
    //fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}