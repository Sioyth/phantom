#include "ShaderGraph.h"
#include <imgui/imgui.h>
#include <iostream>
#include "../../util/Time.h"
static glm::vec3* vec = new glm::vec3(0.0f, 0.0f, 0.0f);
namespace Phantom
{
	GraphContext ShaderGraph::_graphContext;

	class MultiplyNode : public Node
	{
		public:
			MultiplyNode()
			{
				_name = "Multiply";
				AddSlot("A", SlotType::Input);
				AddSlot("B", SlotType::Input);
				AddSlot("Out", SlotType::Output);
			}

			glm::vec3* result = new glm::vec3();

			void Resolve()
			{
				Node::Resolve();

				/*auto first = _inputSlots[0]._data.GetDataAddress();
				auto second = _inputSlots[1]._data.GetDataAddress();*/

				
				
				
				std::cout << "Input 1: " << CastTo<glm::vec3>(_inputSlots[0]._data.GetDataAddress())->x << std::endl;
				//std::cout << "Input 2: " << *(float*)_inputSlots[1]._data.GetData() << std::endl;
				//std::cout << "Input 2: " << *CastTo<double>(_inputSlots[1]._data.GetData()) << std::endl;
				std::cout << "Input 2: " << *CastTo<float>(_inputSlots[1]._data.GetDataAddress()) << std::endl;
				/*std::cout << "Input 2: " << _inputSlots[1]._data.GetDataAddress() << std::endl;
				std::cout << "Result " << _outputSlots[0]._data.GetDataAddress() << std::endl;*/

				glm::vec3* p = CastTo<glm::vec3>(_inputSlots[0]._data.GetDataAddress());
				//*p = *p * (float) * (double*)_inputSlots[1]._data.GetData();
				*result = *p * *CastTo<float>(_inputSlots[1]._data.GetDataAddress());

				std::cout << result->x << ", " << result->y << ", " << result->z << std::endl;

				_outputSlots[0]._data.SetData(result);
				
				auto re = CastTo<glm::vec3>(_outputSlots[0]._data.GetData());
				std::cout << re->x << ", " << re->y << ", " << re->z << std::endl;
			}
	};

	void ShaderGraph::Draw()
	{
		_graphContext.BeginGraph("ShaderGraph");
		static bool firstPass = false;
		if (!firstPass)
		{
			firstPass = true;
			_graphContext.CreateNode(new OutputNode(), ImVec2(250, 250));
			_graphContext.CreateVariable("Time", &Time::DeltaTimeVal(), true, DataType::Double);
		}

		ContextMenu();
		_graphContext.EndGraph();
	}

	void ShaderGraph::ContextMenu()
	{
		bool contextMenuOpen = false;
		static Node* nodeHovered;
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			contextMenuOpen = true;

		if (contextMenuOpen)
		{
			ImGui::OpenPopup("Menu");
			nodeHovered = _graphContext.GetGraph()->_nodeHovered;
		}
		
		if (ImGui::BeginPopup("Menu"))
		{
			if (nodeHovered)
			{
				if (ImGui::MenuItem("Delete"))
					_graphContext.DeleteNode(nodeHovered);
			}
			else
			{
				ImVec2 pos = _graphContext.GetGraphPosition();
				if (ImGui::MenuItem("Create node"))
					_graphContext.CreateNode(new MultiplyNode(), pos);
				if (ImGui::MenuItem("Create variable"))
					_graphContext.CreateVariableOnGraph(new NodeVariable("test", 10, pos, vec, false, DataType::Vec3));
			}
			ImGui::EndPopup();
		}
	}
}

