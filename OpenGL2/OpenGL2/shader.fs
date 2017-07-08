#version 330 core
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
	float ambientstr = 0.1;
	vec3 ambience = ambientstr * lightColor;
	vec3 finalColor = objectColor * ambience;
	FragColor = vec4(finalColor, 1.0) * texture(ourTexture1, TexCoord);
}