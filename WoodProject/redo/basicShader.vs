#version 120

attribute vec3 position;
attribute vec3 texCoord;
attribute vec3 normal;

varying vec3 texCoord0;
varying vec3 normal0;

uniform mat4 MVP;
uniform mat4 Normal;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = (position + vec3(1.f, 1.f, 1.f))/2.f;
	normal0 = (Normal * vec4(normal, 0.0)).xyz;
}