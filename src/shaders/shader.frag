#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D tex;

void main()
{    
    

    FragColor = texture(tex, texCoords);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}