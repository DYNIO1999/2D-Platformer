#type vertex
#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
out vec4 v_Color;
uniform mat4 u_ViewProjection;

void main()
{
    v_Color = a_Color;
	gl_Position = u_ViewProjection* vec4(a_Position.xyz, 1.0);
}

#type fragment
#version 460
layout(location = 0) out vec4 finalColor;
in vec4 v_Color;
void main()
{
    finalColor = v_Color;
}