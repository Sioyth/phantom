#include "OutputNode.h"
#include "../Shader.h"
#include <iostream>

namespace Phantom 
{
	OutputNode::OutputNode()
	{
		_constant = true;
		_name = "Fragment";
		AddSlot("Albedo", SlotType::Input, DataType::Vec3);
	}

	void OutputNode::Resolve()
	{
		Node::Resolve();
		const char* fragmentShaderSource = "#version 460 core\n"
			"struct v2f\n"
			"{\n"
			"	vec4 _position;\n"
			"	vec3 _normal;\n"
			"	vec2 _uvs;\n"
			"};\n"

			"struct Material\n"
			"{\n"
			"	sampler2D _diffuse;\n"
			"	sampler2D _specular;\n"
			"	sampler2D _normal;\n"
			"	sampler2D _displacement;\n"
			"	sampler2D _ambient;\n"

			"	vec3 _color;\n"
			"	float _ambientReflectance;\n"
			"	float _diffuseReflectance;\n"
			"	float _specularReflectance;\n"
			"	float _specularExponent;\n"
			"};\n"

			"struct Light\n"
			"{\n"
			"	vec3 _position;\n"
			"	vec3 _ambientColor;\n"
			"	vec3 _color;\n"
			"};\n"

			"// In out.\n"
			"in v2f _v2f;\n"
			"out vec4 fragColor;\n"

			"// Uniforms\n"
			"uniform Light _light;\n"
			"uniform Material _material;\n"
			"uniform vec3 cameraPos;\n"
			"uniform vec4 _albedo;\n"
			"void main()\n"
			"{\n";

		glm::vec3* albedo = CastTo<glm::vec3>(_inputSlots[0]._data.GetDataAddress());
		if (std::ifstream("shadergraph.frag"))
		{
			std::cout << "File Already Exits" << std::endl;
			std::ofstream file;
			file.open("shadergraph.frag");
			file << fragmentShaderSource;
			//file << "vec3 Ra = _albedo * 0.5f;\n";
			file << "fragColor = vec4(" << albedo->x << "," << albedo->y << "," << albedo->z << "," << "1.0f);\n";
			//file << "vec3 Ra = _albedo;\n";
			//file << "fragColor = _albedo;\n";
			file << "}\n\0";
			file.close();
		}
		else
		{
			std::ofstream file("shadergraph.frag");
			if (!file)
				std::cout << "File could not be created" << std::endl;
		}

		static bool first = false;
		if (first == false)
		{
			first = true;
			Shader::_shaderGraphShader = new Shader("src/shader/default.vert", "shadergraph.frag");
		}
		else
		{
			std::string vertCode = Shader::_shaderGraphShader->Load("src/shader/default.vert");
			std::string fragCode = Shader::_shaderGraphShader->Load("shadergraph.frag");
			Shader::_shaderGraphShader->CompileShaders(vertCode.c_str(), fragCode.c_str());
		}
	}
}
