#include "ShaderGraph.h"
#include <imgui/imgui.h>
#include <iostream>

namespace Phantom
{
	std::vector<Node> ShaderGraph::_nodes;

	// VERY TEMP;
	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

	void ShaderGraph::Render()
	{

		static ImVec2 mouseDrag;
		static bool firsPass = true;
		if (firsPass)
		{
			_nodes.push_back(Node("Node 1"));
			//_nodes.push_back(Node("Node 2"));
			std::cout << "here" << std::endl;
			firsPass = false;
		}

		static bool open = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Shader Graph", &open, ImGuiWindowFlags_NoScrollbar);

		ImVec2 offset = mouseDrag + ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		// Grid
		int gridSize = 32;
		ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
		ImVec2 win_pos = ImGui::GetCursorScreenPos();
		ImVec2 winSize = ImGui::GetWindowSize();

		//// fmodf calculates the reminder of a division we use it to wrap the grid around so it's infinite. 
		//for (int x = fmodf(mouseDrag.x, gridSize); x < winSize.x; x+= gridSize)
		//	drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, winSize.y) + win_pos, GRID_COLOR);
		//for (int y = fmodf(mouseDrag.y, gridSize); y < winSize.y; y += gridSize)
		//	drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(winSize.x, y) + win_pos, GRID_COLOR);

		for (int x = 0.0f; x < winSize.x; x += gridSize)
			drawList->AddLine(ImVec2(x, 0.0f), ImVec2(x, winSize.y), GRID_COLOR);
		for (int y = 0.0f; y < winSize.y; y += gridSize)
			drawList->AddLine(ImVec2(0.0f, y), ImVec2(winSize.x, y), GRID_COLOR);

		//// Node
		//drawList->ChannelsSplit(2);
		//for (int i = 0; i < _nodes.size(); i++)
		//{
		//	ImGui::PushID(i);

		//	// Node Content
		//	drawList->ChannelsSetCurrent(1);
		//	ImGui::BeginGroup(); 
		//	ImGui::Text(_nodes[i]._name.c_str());
		//	ImGui::Separator();
		//	ImGui::EndGroup();

		//	// Node Box
		//	drawList->ChannelsSetCurrent(0);
		//	ImGui::InvisibleButton("node", ImVec2(100, 100));
		//	drawList->AddRectFilled(ImVec2(win_pos.x, win_pos.y) + offset, ImVec2(win_pos.x + 100.0f, win_pos.y + 100.0f) + offset, IM_COL32(255, 0, 0, 255), 4.0f);
		//	drawList->AddRect(ImVec2(0, 0), ImVec2(100, 100), IM_COL32(255, 0, 0, 255), 4.0f);

		//	ImGui::PopID();
		//}
		//drawList->ChannelsMerge();

		// Scrolling
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
			mouseDrag = mouseDrag + ImGui::GetIO().MouseDelta;
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
