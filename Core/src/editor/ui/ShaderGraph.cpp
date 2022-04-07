#include "ShaderGraph.h"
#include <imgui/imgui.h>
#include <iostream>
#include "../../ui/graph/Graph.h"

namespace Phantom
{
	ImVec2 ShaderGraph::_mouseDrag;
	//Node* ShaderGraph::_nodeHovered;
	ImDrawList* ShaderGraph::_drawList;
	ImVec2 ShaderGraph::_offset;
	//std::list<Node> ShaderGraph::_nodes;

	// VERY TEMP;
	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

	void ShaderGraph::Render()
	{

		static GraphContext _graphContext;

		_graphContext.BeginGraph("ShaderGraph");
		_graphContext.EndGraph();
		//static unsigned int idCount = 0;

		//static bool open = true;
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		//ImGui::Begin("Shader Graph", &open, ImGuiWindowFlags_NoScrollbar);

		//_drawList = ImGui::GetWindowDrawList();
		//_offset = _mouseDrag + ImGui::GetCursorScreenPos();

		//DrawGrid();

		//for (std::list<Node>::iterator node = _nodes.begin(); node != _nodes.end(); node++)
		//	DrawNode(*node);

		//// Context menu
		//bool contextMenuOpen = false;
		//if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseClicked(1))
		//	contextMenuOpen = true;

		//if (contextMenuOpen)
		//	ImGui::OpenPopup("Menu");

		//if (ImGui::BeginPopup("Menu"))
		//{
		//	if (_nodeHovered == nullptr)
		//	{
		//		ImVec2 scene_pos = ImGui::GetMousePosOnOpeningCurrentPopup() - _offset;
		//		if (ImGui::MenuItem("Create node"))
		//			_nodes.push_back(Node("Node", idCount++, scene_pos));
		//	}
		//	else
		//	{
		//		if (ImGui::MenuItem("Delete"))
		//		{
		//			//_nodes.erase(nodeHovered);
		//			//nodeHovered = _nodes.end();
		//		}
		//	}
		//	ImGui::EndPopup();
		//}
		
		//// Mouse Drag
		//if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
		//	_mouseDrag = _mouseDrag + ImGui::GetIO().MouseDelta;

		//ImGui::End();
		//ImGui::PopStyleVar();
	}

	void ShaderGraph::DrawGrid()
	{
		int _gridSize = 32;
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 win_pos = ImGui::GetCursorScreenPos();
		ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);

		// fmodf calculates the reminder of a division we use it to wrap the grid around so it's infinite. 
		for (int x = fmodf(_mouseDrag.x, _gridSize); x < winSize.x; x += _gridSize)
			_drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, winSize.y) + win_pos, GRID_COLOR);
		for (int y = fmodf(_mouseDrag.y, _gridSize); y < winSize.y; y += _gridSize)
			_drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(winSize.x, y) + win_pos, GRID_COLOR);
	}

	//void ShaderGraph::DrawNode(Node& node)
	//{
	//	//ImGui::PushID(node._id);
	//	//_drawList->ChannelsSplit(3);

	//	//// 
	//	//ImVec2 nodeBoxMinSize = ImVec2(150.0f, 50.0f);
	//	//ImVec2 nodeBoxTopLeftCorner = node._position + _offset;
	//	//ImVec2 nodeBoxPadding = ImVec2(10.0f, 8.0f);
	//	//ImVec4 headerPadding = ImVec4(10.0f, 5.0f, 0.0f, 0.0f); // Top - Bottom - Left - Right padding
	//	//ImVec2 headerTitleSize = ImGui::CalcTextSize(node._name.c_str());
	//	//ImVec2 contentPosition = ImVec2(nodeBoxTopLeftCorner + nodeBoxPadding);
	//	//contentPosition.y += headerTitleSize.y + headerPadding.x;

	//	//// Node Content
	//	//_drawList->ChannelsSetCurrent(2);
	//	//ImGui::SetCursorScreenPos(nodeBoxTopLeftCorner + nodeBoxPadding);
	//	//ImGui::BeginGroup();
	//	//ImGui::Text(node._name.c_str());
	//	//ImGui::SetCursorScreenPos(contentPosition);
	//	//ImGui::Text("Dummy");
	//	//ImGui::Text("Dummy");
	//	//ImGui::Text("Dummy");
	//	//ImGui::EndGroup();

	//	//// Set Window Sized based on the size of the node window created Make a invisible button the size of the window so it can be interacted with (E.g hovered, clicked)
	//	//ImVec2 windowSize = ImGui::GetItemRectSize() + nodeBoxPadding + nodeBoxPadding;
	//	//windowSize.x = windowSize.x < nodeBoxMinSize.x ? nodeBoxMinSize.x : windowSize.x;
	//	//windowSize.y = windowSize.y < nodeBoxMinSize.y ? nodeBoxMinSize.y : windowSize.y;
	//	//ImVec2 nodeBoxBottomRightCorner = nodeBoxTopLeftCorner + windowSize;
	//	//ImGui::SetCursorScreenPos(nodeBoxTopLeftCorner);
	//	//ImGui::InvisibleButton("node", windowSize);

	//	//if (ImGui::IsItemHovered())
	//	//	_nodeHovered = &node;
	//	//else
	//	//	_nodeHovered = nullptr;

	//	//bool nodeIsSelected = ImGui::IsItemActive();
	//	//if (nodeIsSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	//	//	node._position = node._position + ImGui::GetIO().MouseDelta;

	//	//// Node Box Header
	//	//_drawList->ChannelsSetCurrent(1);
	//	//ImU32 headerBgColor = _nodeHovered == &node || nodeIsSelected ? IM_COL32(60, 80, 60, 255) : IM_COL32(60, 90, 60, 255);
	//	//ImVec2 headerSize = ImVec2(windowSize.x, headerTitleSize.y + nodeBoxPadding.y + headerPadding.y);
	//	//_drawList->AddRectFilled(nodeBoxTopLeftCorner, nodeBoxTopLeftCorner + headerSize, headerBgColor, 4.0f, ImDrawFlags_RoundCornersTop);
	//	//_drawList->AddLine(ImVec2(nodeBoxTopLeftCorner.x, nodeBoxTopLeftCorner.y + headerSize.y), nodeBoxTopLeftCorner + headerSize, IM_COL32(100, 100, 100, 255));

	//	//// Node Box Background
	//	//ImU32 nodeBgBackground = _nodeHovered == &node || nodeIsSelected ? IM_COL32(50, 50, 50, 255) : IM_COL32(60, 60, 60, 255);
	//	//_drawList->ChannelsSetCurrent(0);
	//	//_drawList->AddRectFilled(nodeBoxTopLeftCorner, nodeBoxBottomRightCorner, nodeBgBackground, 4.0f);
	//	//_drawList->AddRect(nodeBoxTopLeftCorner, nodeBoxBottomRightCorner, IM_COL32(100, 100, 100, 255), 4.0f);

	//	//// 
	//	//_drawList->ChannelsSetCurrent(1);
	//	//ImVec2 circleCenter = ImVec2(nodeBoxTopLeftCorner.x, contentPosition.y + ImGui::CalcTextSize("Dummy").y * 0.5f);
	//	//_drawList->AddCircleFilled(circleCenter, 4.0f, IM_COL32(255, 0, 5, 255));
	//	///*_drawList->AddCircle(circleCenter, 4.0f, IM_COL32(255, 0, 5, 255));
	//	//_drawList->AddLine(circleCenter, ImVec2(circleCenter.x + 100.0f, circleCenter.y), IM_COL32(60, 90, 60, 255), 1.0f);*/

	//	///*circleCenter = ImVec2(node_rect_min.x, node_rect_min.y + headerSize.y + headerPadding.y + ImGui::CalcTextSize("Dummy").y);
	//	//_drawList->AddLine(circleCenter, ImVec2(circleCenter.x + 100.0f, circleCenter.y), IM_COL32(60, 90, 60, 255), 1.0f);*/

	//	//ImGui::PopID();
	//	//_drawList->ChannelsMerge();
	//}
}