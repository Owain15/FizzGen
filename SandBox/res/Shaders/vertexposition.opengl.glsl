
// Vertex Shader color is set in the vertex buffer and passed to the fragment shader
// OpenGL for X64 builds

#type vertex

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Color = a_Color;
}


#type fragment

#version 330 core

in vec4 v_Color;
				
out vec4 FragColor;

void main()
{
	FragColor = v_Color;
}
