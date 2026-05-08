// One shader to handel both textures and colors 
// ANGLE for ARM64 builds
// ANGLE does not support geometry shaders, so we will use a vertex shader to pass the color to the fragment shader.

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

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform int u_TextureTileCount;
uniform vec4 u_FragColor;
uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoords * float(u_TextureTileCount)) * u_FragColor;
}