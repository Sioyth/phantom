#include "Graph.h"
#include <iostream>

namespace Phantom
{
	// VERY TEMP;
	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

	GraphContext::GraphContext()
	{
		_graphs["ShaderGraph"]._nodes.push_back(Node(0, ImVec2(0, 0)));
		Slot slot;
		slot._data = 5;
		slot._name = "UV";
		_graphs["ShaderGraph"]._nodes.front()._inputSlots.push_back(slot);
		_graphs["ShaderGraph"]._nodes.front()._inputSlots.push_back(slot);
		//_graphs["ShaderGraph"]._nodes.front()._inputSlots.push_back(slot);


		slot._name = "Out";
		_graphs["ShaderGraph"]._nodes.front()._outputSlots.push_back(slot);
		_graphs["ShaderGraph"]._nodes.front()._outputSlots.push_back(slot);
		_graphs["ShaderGraph"]._nodes.front()._outputSlots.push_back(slot);
	}

	void GraphContext::BeginGraph(const char* name, GraphFlags flags)
	{
		static bool open = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin(name, &open, ImGuiWindowFlags_NoScrollbar);

		_currentGraph = &_graphs[name];
		_currentGraph->_drawList = ImGui::GetWindowDrawList();
		_currentGraph->_offset = _currentGraph->_mouseDrag + ImGui::GetCursorScreenPos();

		if(!flags & NoGrid) 
			DrawGrid(name);

		for (std::list<Node>::iterator node = _currentGraph->_nodes.begin(); node != _currentGraph->_nodes.end(); node++)
			DrawNodeWindow(*node);

		bool contextMenuOpen = false;
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseClicked(1))
			contextMenuOpen = true;

		if (contextMenuOpen)
			ImGui::OpenPopup("Menu");

		if (ImGui::BeginPopup("Menu"))
		{
			ImVec2 scene_pos = ImGui::GetMousePosOnOpeningCurrentPopup() - _graphs[name]._offset;
			if (ImGui::MenuItem("Create node"))
				CreateNode(name, scene_pos);
			ImGui::EndPopup();
		}

		// Mouse Drag
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
			_graphs[name]._mouseDrag = _graphs[name]._mouseDrag + ImGui::GetIO().MouseDelta;
	}

	void GraphContext::EndGraph()
	{
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void GraphContext::CreateNode(const char* name, const ImVec2& pos)
	{
		_guid++;
		_graphs[name]._nodes.push_back(Node(_guid, pos));
	}

	void GraphContext::DrawGrid(const char* name)
	{
		int gridSize = 32;
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 win_pos = ImGui::GetCursorScreenPos();
		ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);

		// fmodf calculates the reminder of a division we use it to wrap the grid around so it's infinite. 
		for (int x = fmodf(_graphs[name]._mouseDrag.x, gridSize); x < winSize.x; x += gridSize)
			_graphs[name]._drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, winSize.y) + win_pos, GRID_COLOR);
		for (int y = fmodf(_graphs[name]._mouseDrag.y, gridSize); y < winSize.y; y += gridSize)
			_graphs[name]._drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(winSize.x, y) + win_pos, GRID_COLOR);
	}

	void GraphContext::DrawNodeWindow(Node& node)
	{
		ImGui::PushID(node._id);
		_currentGraph->_drawList->ChannelsSplit(3);

		// temp move this to some configish file
		ImVec2 nodeWindomMinSize = ImVec2(150.0f, 50.0f);
		ImVec2 nodeWindowTopLeftCorner = node._position + _currentGraph->_offset;
		ImVec2 nodeWindowPadding = ImVec2(10.0f, 8.0f);
		ImVec4 headerPadding = ImVec4(10.0f, 5.0f, 0.0f, 0.0f); // Top - Bottom - Left - Right padding
		ImVec2 headerTitleSize = ImGui::CalcTextSize(node._name);
		ImVec2 contentPosition = ImVec2(nodeWindowTopLeftCorner + nodeWindowPadding);
		contentPosition.y += headerTitleSize.y + headerPadding.x;

		static ImVec2 windowSize = ImVec2(node.CalcNodeWidth(), 0.0f);
		windowSize.x = windowSize.x < nodeWindomMinSize.x ? nodeWindomMinSize.x : windowSize.x;
		windowSize.y = windowSize.y < nodeWindomMinSize.y ? nodeWindomMinSize.y : windowSize.y;

		// Node Content
		_currentGraph->_drawList->ChannelsSetCurrent(2);
		ImGui::SetCursorScreenPos(nodeWindowTopLeftCorner + nodeWindowPadding);
		ImGui::BeginGroup();
		ImGui::Text(node._name);
		ImGui::SetCursorScreenPos(contentPosition);
		
		float size = node._inputSlots.size() >= node._outputSlots.size() ? node._inputSlots.size() : node._outputSlots.size();
		for (int i = 0; i < size; i++)
		{
			if (i < node._inputSlots.size())
			{
				ImGui::Text(node._inputSlots[i]._name);
				ImVec2 circleCenter = ImVec2(nodeWindowTopLeftCorner.x, ImGui::GetCursorScreenPos().y - ImGui::CalcTextSize(node._outputSlots[i]._name).y + ImGui::GetStyle().ItemSpacing.y);
				_currentGraph->_drawList->AddCircleFilled(circleCenter, 4.0f, IM_COL32(255, 0, 5, 255));
			}

			if (i < node._outputSlots.size())
			{	
				if (i < node._inputSlots.size())
					ImGui::SameLine(windowSize.x - ImGui::CalcTextSize(node._outputSlots[i]._name).x - nodeWindowPadding.x - nodeWindowPadding.x);
				else
					ImGui::SetCursorScreenPos(ImGui::GetCursorScreenPos() + ImVec2(windowSize.x - ImGui::CalcTextSize(node._outputSlots[i]._name).x - nodeWindowPadding.x - nodeWindowPadding.x, 0.0f));
				ImGui::Text(node._outputSlots[i]._name);

				ImVec2 circleCenter = ImVec2(nodeWindowTopLeftCorner.x + windowSize.x, ImGui::GetCursorScreenPos().y - ImGui::CalcTextSize(node._outputSlots[i]._name).y + ImGui::GetStyle().ItemSpacing.y);
				_currentGraph->_drawList->AddCircleFilled(circleCenter, 4.0f, IM_COL32(255, 0, 5, 255));
				//ImGui::InvisibleButton()
			}
		}

		ImGui::EndGroup();

		// Set the window size and make an invisible button the size of it to be possible to be interacted with (E.g hovered, clicked, dragged around)
		windowSize = ImVec2(node.CalcNodeWidth(), ImGui::GetItemRectSize().y) + nodeWindowPadding + nodeWindowPadding;
		windowSize.x = windowSize.x < nodeWindomMinSize.x ? nodeWindomMinSize.x : windowSize.x;
		windowSize.y = windowSize.y < nodeWindomMinSize.y ? nodeWindomMinSize.y : windowSize.y;
		ImVec2 nodeBoxBottomRightCorner = nodeWindowTopLeftCorner + windowSize;
		ImGui::SetCursorScreenPos(nodeWindowTopLeftCorner);
		ImGui::InvisibleButton("node", windowSize);

		if (ImGui::IsItemHovered())
			_currentGraph->_nodeHovered = &node;
		else
			_currentGraph->_nodeHovered = nullptr;

		bool nodeIsSelected = ImGui::IsItemActive();
		if (nodeIsSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			node._position = node._position + ImGui::GetIO().MouseDelta;

		// Node Box Header
		_currentGraph->_drawList->ChannelsSetCurrent(1);
		ImU32 headerBgColor = _currentGraph->_nodeHovered == &node || nodeIsSelected ? IM_COL32(60, 80, 60, 255) : IM_COL32(60, 90, 60, 255);
		ImVec2 headerSize = ImVec2(windowSize.x, headerTitleSize.y + nodeWindowPadding.y + headerPadding.y);
		_currentGraph->_drawList->AddRectFilled(nodeWindowTopLeftCorner, nodeWindowTopLeftCorner + headerSize, headerBgColor, 4.0f, ImDrawFlags_RoundCornersTop);
		_currentGraph->_drawList->AddLine(ImVec2(nodeWindowTopLeftCorner.x, nodeWindowTopLeftCorner.y + headerSize.y), nodeWindowTopLeftCorner + headerSize, IM_COL32(100, 100, 100, 255));

		// Node Box Background
		ImU32 nodeBgBackground = _currentGraph->_nodeHovered == &node || nodeIsSelected ? IM_COL32(50, 50, 50, 255) : IM_COL32(60, 60, 60, 255);
		_currentGraph->_drawList->ChannelsSetCurrent(0);
		_currentGraph->_drawList->AddRectFilled(nodeWindowTopLeftCorner, nodeBoxBottomRightCorner, nodeBgBackground, 4.0f);
		_currentGraph->_drawList->AddRect(nodeWindowTopLeftCorner, nodeBoxBottomRightCorner, IM_COL32(100, 100, 100, 255), 4.0f);

		ImGui::PopID();
		_currentGraph->_drawList->ChannelsMerge();
	}

	void GraphContext::DrawLinks()
	{
		/*for (int i = 0; i < _currentGraph->_links.size(); i++)
		{
			
		}*/
	}

	void GraphContext::DrawSlot(const ImVec2& center)
	{
		_currentGraph->_drawList->AddCircle(center, 4.0f, IM_COL32(255, 0, 5, 255));
	}
}
