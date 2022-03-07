#version 460 core
out vec4 fragColor;
in vec2 TexCoords;
uniform vec4 color;

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
};

uniform Material material;

void main()
{
	//fragColor = vec4(color);
	
	fragColor = texture(material.texture_diffuse1, TexCoords) * color;
}