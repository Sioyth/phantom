#version 460 core
struct v2f
{
	vec4 _position;
	vec3 _normal;
	vec2 _uvs;
};
struct Material
{
	sampler2D _diffuse;
	sampler2D _specular;
	sampler2D _normal;
	sampler2D _displacement;
	sampler2D _ambient;
	vec3 _color;
	float _ambientReflectance;
	float _diffuseReflectance;
	float _specularReflectance;
	float _specularExponent;
};
struct Light
{
	vec3 _position;
	vec3 _ambientColor;
	vec3 _color;
};
// In out.
in v2f _v2f;
out vec4 fragColor;
// Uniforms
uniform Light _light;
uniform Material _material;
uniform vec3 cameraPos;
uniform float _time;
void main()
{
fragColor = vec4(3.11765 ,0.672434,0.672434,1.0f);
}
