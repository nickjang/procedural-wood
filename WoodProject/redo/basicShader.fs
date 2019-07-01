#version 120

varying vec3 texCoord0;
varying vec3 normal0;

uniform sampler3D sampler;
uniform vec3 lightDirection;

void main()
{
	//gl_FragColor = vec4(texCoord0.x, texCoord0.y, texCoord0.z, 1.f);
	gl_FragColor = texture3D(sampler, texCoord0).rgba * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}