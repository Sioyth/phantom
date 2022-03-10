#version 460 core

struct v2f
{
	vec4 _position;
	vec3 _normal;
	vec2 _uvs;
};

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;

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

void main()
{
	//Ambient
	vec3 Ra = _light._ambientColor * _material._ambientReflectance * texture(_material.texture_diffuse1, _v2f._uvs).rgb *_material._color;

	// Diffuse
	vec3 L = normalize(_light._position - vec3(_v2f._position.xyz));
	vec3 N = normalize(_v2f._normal);

	float angle = dot(N, L);
	vec3 Rd = _light._color * _material._diffuseReflectance * angle;

	//Specular
	vec3 H = normalize(L + cameraPos);
	vec3 Rs = _light._color * _material._specularReflectance * pow(dot(N, H), _material._specularExponent);

   vec3 p = vec3(_v2f._position.xyz);
   float d = length(_light._position - p);
   float attenuation2 = 1 / pow(d, 2);

	vec3 Rp = Ra + attenuation2 * (Rd + Rs);

	//fragColor = vec4(1.0);
	fragColor = vec4(Rp, 1.0f);
}