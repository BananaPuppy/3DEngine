#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 AtlasCoords;

uniform sampler2D texture1;

void main()
{
    vec4 amongus_tex = texture2D(texture1, AtlasCoords);
    
    FragColor = (amongus_tex);
}

vec2 saturate(vec2 var)
{ return clamp(var,0.0,1.0); }