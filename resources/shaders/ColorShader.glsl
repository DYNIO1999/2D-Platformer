#type vertex
#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
out vec3 v_Position;
uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
void main()
{
	gl_Position = u_ViewProjection*u_Model*vec4(a_Position.xyz, 1.0);
}

#type fragment
#version 460
layout(location = 0) out vec4 finalColor;
uniform vec4 u_Color;
void main()
{
    finalColor = u_Color;
}