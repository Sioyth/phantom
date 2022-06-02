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
uniform vec4 _albedo;
void main()
{
fragColor = vec4(5.39586e-15,4.59079e-41,2.8026e-45,1.0f);
}
