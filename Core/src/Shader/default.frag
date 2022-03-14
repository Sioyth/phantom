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

void main()
{
	//Ambient
	vec3 Ra = _light._ambientColor * _material._ambientReflectance * _material._color;
	//vec3 Ra = _light._ambientColor * _material._ambientReflectance *_material._color;

	// Diffuse
	vec3 L = normalize(_light._position - _v2f._position.xyz);
	vec3 N = normalize(_v2f._normal);

	float diffuseModulation = max(dot(N, L), 0.0);
	//vec3 Rd = _light._color * _material._diffuseReflectance * angle * texture(_material._diffuse, _v2f._uvs).rgb;
	vec3 Rd = _light._color * _material._diffuseReflectance * diffuseModulation * _material._color;;

	//Specular
	vec3 V = normalize(cameraPos - _v2f._position.xyz);
	vec3 H = normalize(L + cameraPos);
	float specModulation = pow(max(dot(H, N), 0.0), _material._specularExponent);
	//vec3 Rs = _light._color * _material._specularReflectance * pow(dot(N, H), _material._specularExponent) * texture(_material._specular, _v2f._uvs).rgb;
	vec3 Rs = _light._color * _material._specularReflectance * specModulation;

//    vec3 p = vec3(_v2f._position.xyz);
//    float d = length(_light._position - p);
//    float attenuation = 1 / pow(d, 2);

   float distToLight = distance(_light._position, _v2f._position.xyz);
   float attenuation = 1.0 / (distToLight * distToLight);

	vec3 Rp = Ra + (Rd + Rs) * attenuation;

	fragColor = vec4(1.0);
	//fragColor = vec4(Rp, 1.0f);
}