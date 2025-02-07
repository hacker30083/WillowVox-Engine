#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;

uniform bool underwater;

const vec3 fogColor = vec3(0, 0, 0.25);
const float fogNear = 0.9;
const float fogFar = 1.0;

void main()
{
	vec4 color = texture(screenTexture, TexCoords);

	FragColor = color;
}