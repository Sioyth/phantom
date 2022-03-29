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


	struct MeshRenderer
	{
		Phantom::Model _model;
		Phantom::Material _material;

		MeshRenderer(const MeshRenderer&) = default;
		MeshRenderer(const Phantom::Model& model) : _model(model) {};
	};

	struct Light
	{
		float _intensity;
		glm::vec3 _color;
		LightType _type;

		Light() = default;
		Light(const Light&) = default;
		Light(const glm::vec3& color = glm::vec3(1.0f), const float& intensity = 1.0f, const LightType& type = LightType::Spot) : _color(color), _intensity(intensity), _type(type) {};
	};

	struct Tag
	{
		//Model;
		std::string _name;
		Tag() = default;
		Tag(const Tag&) = default;
		Tag(const std::string& name) : _name(name) {};
	};
}