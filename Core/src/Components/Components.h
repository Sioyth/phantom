#pragma once
#include <glm/glm.hpp>
#include <string>
#include "../render/Model.h"
#include "../shader/Material.h"

namespace Phantom
{
	enum LightType
	{
		Directional, Point, Spot, Area
	};
}

struct MeshRenderer
{
	Phantom::Model _model;
	Phantom::Material _material;

	MeshRenderer(const Phantom::Model& model) : _model(model) {};
	MeshRenderer(const MeshRenderer&) = default;
	//MeshRenderer(const glm::mat4 & matrix) : _matrix(matrix) {};
};



struct Light
{
	float _intensity;
	glm::vec3 _color;
	//Phantom::LightType _type = Phantom::LightType::Spot;

	Light() = default;
	Light(const Light&) = default;
	Light(const glm::vec3& color) : _color(color) {};
};

struct Tag
{
	//Model;
	std::string _name;
	Tag() = default;
	Tag(const Tag&) = default;
	Tag(const std::string& name) : _name(name) {};
};