#include "OutputNode.h"
#include "../Shader.h"

namespace Phantom 
{
	OutputNode::OutputNode()
	{
		_constant = true;
		_name = "Fragment";
		AddSlot("Albedo", SlotType::Input);
	}

	void OutputNode::Resolve()
	{
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";

		Shader temp = Shader("src/shader/default.vert", "src/shader/default.frag");
	}
}
