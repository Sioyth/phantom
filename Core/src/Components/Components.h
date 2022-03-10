#pragma once
#include <glm/glm.hpp>
#include <string>
#include "mesh/Model.h"
#include "Shader/Material.h"

struct Transform 
{
	glm::mat4 _matrix = glm::mat4(1.0f);

	Transform() = default;
	Transform(const Transform&) = default;
	Transform(const glm::mat4& matrix) : _matrix(matrix) {};
};

struct MeshRenderer
{
	Phantom::Model _model;
	Phantom::Material _material;

	MeshRenderer(const Phantom::Model& model) : _model(model) {};
	MeshRenderer(const MeshRenderer&) = default;
	//MeshRenderer(const glm::mat4 & matrix) : _matrix(matrix) {};
};

struct Camera
{
	bool mainCamera;
	glm::mat4 _fov;
	glm::mat4 _proj;
	glm::mat4 _viewMatrix;
};

struct Light
{
	glm::vec3 _color;

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