#type vertex
#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
out vec3 v_Position;
out vec2 v_TextCoord;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
void main()
{
	v_TextCoord = a_TexCoord;
	gl_Position = u_Projection*u_View*u_Model*vec4(a_Position.xyz, 1.0);
}

#type fragment
#version 460
layout(location = 0) out vec4 finalColor;
uniform sampler2D u_Texture;
in vec2 v_TextCoord;

void main()
{
	vec4 texColor = texture(u_Texture,v_TextCoord);
    finalColor = texColor;
}