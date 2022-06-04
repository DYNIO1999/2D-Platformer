#type vertex
#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
out vec3 v_Position;

void main()
{
	gl_Position = vec4(a_Position.xyz, 1.0);;
}

#type fragment
#version 460

layout(location = 0) out vec4 finalColor;

void main()
{
	finalColor = vec4(0.5,0.3,0.7,1.0); 
}