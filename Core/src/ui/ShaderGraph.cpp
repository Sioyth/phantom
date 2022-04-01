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

		// fmodf calculates the reminder of a division we use it to wrap the grid around so it's infinite. 
		for (int x = fmodf(mouseDrag.x, gridSize); x < winSize.x; x+= gridSize)
			drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, winSize.y) + win_pos, GRID_COLOR);
		for (int y = fmodf(mouseDrag.y, gridSize); y < winSize.y; y += gridSize)
			drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(winSize.x, y) + win_pos, GRID_COLOR);

		// Node
		drawList->ChannelsSplit(3);
		for (int i = 0; i < _nodes.size(); i++)
		{
			ImGui::PushID(i);

			ImVec2 windowMinSize = ImVec2(150.0f, 50.0f);
			ImVec2 node_rect_min = win_pos + offset;
			ImVec2 windowPadding = ImVec2(10.0f, 8.0f);
			ImVec4 headerPadding = ImVec4(5.0f, 5.0f, 0.0f, 0.0f); // Top - Bottom - Left - Right padding
			ImVec2 headerTitleSize = ImGui::CalcTextSize(_nodes[i]._name.c_str());

			// Node Content
			drawList->ChannelsSetCurrent(2);
			ImGui::SetCursorScreenPos(node_rect_min + windowPadding);
			ImGui::BeginGroup(); 
			ImGui::Text(_nodes[i]._name.c_str());
			ImVec2 temp = ImVec2(node_rect_min + windowPadding);
			temp.y += headerTitleSize.y + headerPadding.y + headerPadding.x;
			ImGui::SetCursorScreenPos(temp);
			ImGui::Text("Dummy");
			ImGui::Text("Dummy");
			ImGui::Text("Dummy");
			ImGui::EndGroup();

			ImVec2 windowSize = ImGui::GetItemRectSize() + windowPadding + windowPadding;
			windowSize.x = windowSize.x < windowMinSize.x ? windowMinSize.x : windowSize.x;
			windowSize.y = windowSize.y < windowMinSize.y ? windowMinSize.y : windowSize.y;
			ImVec2 node_rect_max = node_rect_min + windowSize;

			// Node Box Header
			drawList->ChannelsSetCurrent(1);
			ImVec2 headerSize = ImVec2(windowSize.x, headerTitleSize.y + windowPadding.y + headerPadding.y);
			drawList->AddRectFilled(node_rect_min, node_rect_min + headerSize, IM_COL32(60, 90, 60, 255), 4.0f);
			drawList->AddLine(ImVec2(node_rect_min.x, node_rect_min.y + headerSize.y), node_rect_min + headerSize, IM_COL32(100, 100, 100, 255));

			// Node Box Background
			drawList->ChannelsSetCurrent(0);
			ImGui::SetCursorScreenPos(node_rect_min);
			ImGui::InvisibleButton("node", windowSize);
			drawList->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(60, 60, 60, 255), 4.0f);
			drawList->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);

			// 
			drawList->ChannelsSetCurrent(1);
			ImVec2 circleCenter = ImVec2(node_rect_min.x, node_rect_min.y + headerSize.y + headerPadding.y + headerPadding.x);
			drawList->AddCircleFilled(circleCenter, 4.0f, IM_COL32(255, 0, 5, 255));


			ImGui::PopID();
		}
		drawList->ChannelsMerge();

		// Scrolling
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
			mouseDrag = mouseDrag + ImGui::GetIO().MouseDelta;
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
