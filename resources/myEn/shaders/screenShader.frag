#version 460 core
out vec4 fragColor;

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{    
    

    fragColor = texture(tex, TexCoords);
    //fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}