

// flat color shader, set color uniform to change color of the object
// OpenGL, for X64 builds 


#type vertex

#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;

void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}


#type fragment

#version 330 core

in vec3 v_Position;

out vec4 FragColor;

uniform vec3 u_Color;

void main()
{
	FragColor = vec4(u_Color, 1.0);
}


