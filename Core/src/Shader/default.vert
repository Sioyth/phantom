#version 460 core
layout(location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs;

uniform mat4 mvp;
uniform mat4 model;

struct v2f
{
	vec4 _position;
	vec3 _normal;
	vec2 _uvs;
};

out v2f _v2f;

void main()
{
	_v2f._uvs = uvs;
	_v2f._position = model * vec4(position, 1.0); // world pos
	_v2f._normal = normalize(model * vec4(normal, 0.0)).xyz;
	gl_Position = mvp * vec4(position, 1.0);
}