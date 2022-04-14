#include "ShaderGraph.h"
#include <imgui/imgui.h>
#include <iostream>

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

			void Resolve()
			{
				Node::Resolve();
				_outputSlots[0]._data = _inputSlots[0]._data * _inputSlots[1]._data;
				std::cout << "Input 1: " << _inputSlots[0]._data << std::endl;
				std::cout << "Input 2: " << _inputSlots[1]._data << std::endl;
				std::cout << "Result " << _outputSlots[0]._data << std::endl;
			}
	};

	void ShaderGraph::Draw()
	{
		_graphContext.BeginGraph("ShaderGraph");
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
					_graphContext.CreateVariable(pos);
			}
			ImGui::EndPopup();
		}
	}
}