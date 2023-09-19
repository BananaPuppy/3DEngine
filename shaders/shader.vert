#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aAtlasCoords;

out vec4 vertexColor;
out vec2 AtlasCoords;

uniform float time;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec2 TexCoords;

void main()
{
	//gl_Position = transform * vec4(aPos, 1.0f);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//Vclip = Mprojection * Mview * Mmodel * Vlocal
	AtlasCoords = vec2((aAtlasCoords.x/10), aAtlasCoords.y);
	vertexColor = vec4(aPos, 1.0f);
}

	//vec3 rainbow = rainbowColors(aPos, 0.5, 0);
//vec3 rainbowColors(vec3 vec, float speed, float angle)
//{
//	//Epic spiky time func
//	float stime = max(2*(-abs(mod(time, 1))+1), 1.0f) * max(2*(abs(mod(time, 1))), 1.0f); stime -= 1;
//
//	float hue = (vec.x * cos(radians(angle))) - (vec.y * sin(radians(angle)));
//	hue = fract(hue + fract(stime * speed));
//	vec.x = 1. - abs(mod(hue / (1./ 6.), 2.) - 1.);
//    
//	vec3 rainbow;
//	if(hue < 1./6.){ rainbow = vec3(1., vec.x, 0.); }
//	else if (hue < 1.0f/3.0f) { rainbow = vec3(vec.x, 1.0f, 0.0f); }
//	else if (hue < 0.5f) { rainbow = vec3(0.0f, 1.0f, vec.x); }
//	else if (hue < 2.0f/3.0f) { rainbow = vec3(0.0f, vec.x, 1.0f); }
//	else if (hue < 5.0f/6.0f) { rainbow = vec3(vec.x, 0.0f, 1.0f); }
//	else { rainbow = vec3(1.0f, 0.0f, vec.x); }
//
//	return rainbow;
//}