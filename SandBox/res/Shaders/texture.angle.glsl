// angle version of the texture shader for OpenGL ES 3.0
// FizzGen Arm64 builds

#type vertex
#version 300 es

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 300 es

precision mediump float;

in vec2 v_TexCoords;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoords);
}