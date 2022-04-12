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
		_graphs["ShaderGraph"]._nodes.front().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.front().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.front().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.front().AddSlot("Out", SlotType::Output);
		_graphs["ShaderGraph"]._nodes.front().AddSlot("Out", SlotType::Output);

		_graphs["ShaderGraph"]._nodes.push_back(Node(1, ImVec2(100, 0)));
		_graphs["ShaderGraph"]._nodes.back().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.back().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.back().AddSlot("UV", SlotType::Input);
		_graphs["ShaderGraph"]._nodes.back().AddSlot("Out", SlotType::Output);
		_graphs["ShaderGraph"]._nodes.back().AddSlot("Out", SlotType::Output);
	}

	void GraphContext::BeginGraph(const char* name, GraphFlags flags)
	{
		static bool open = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin(name, &open, ImGuiWindowFlags_NoScrollbar);

		_currentGraph = &_graphs[name];
		_currentGraph->_drawList = ImGui::GetWindowDrawList();
		_currentGraph->_offset = _currentGraph->_mouseDrag + ImGui::GetCursorScreenPos();

		if (!flags & NoGrid)
			DrawGrid();

		for (std::list<Node>::iterator node = _currentGraph->_nodes.begin(); node != _currentGraph->_nodes.end(); node++)
			DrawNodeWindow(*node);

		DrawLinks();

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

	void GraphContext::DrawGrid()
	{
		GraphStyle* style = &_currentGraph->_style;
		GraphColors* colors = &_currentGraph->_colorsStyle;
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 win_pos = ImGui::GetCursorScreenPos();

		// fmodf calculates the reminder of a division we use it to wrap the grid around so it's infinite. 
		for (int x = fmodf(_currentGraph->_mouseDrag.x, style->gridSize); x < winSize.x; x += style->gridSize)
			_currentGraph->_drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, winSize.y) + win_pos, colors->_grid);
		for (int y = fmodf(_currentGraph->_mouseDrag.y, style->gridSize); y < winSize.y; y += style->gridSize)
			_currentGraph->_drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(winSize.x, y) + win_pos, colors->_grid);
	}

	void GraphContext::DrawNodeWindow(Node& node)
	{
		ImGui::PushID(node._id);
		_currentGraph->_drawList->ChannelsSplit(3);

		GraphStyle* style = &_currentGraph->_style;
		GraphColors* colors = &_currentGraph->_colorsStyle;

		ImVec2 nodeWindowTopLeftCorner = node._position + _currentGraph->_offset;
		ImVec2 headerTitleSize = ImGui::CalcTextSize(node._name);
		ImVec2 contentPosition = ImVec2(nodeWindowTopLeftCorner + style->windowPadding);
		contentPosition.y += headerTitleSize.y + style->headerPadding.x;

		static ImVec2 windowSize = ImVec2(node.CalcNodeWidth(), 0.0f);
		windowSize.x = windowSize.x < style->windowMinSize.x ? style->windowMinSize.x : windowSize.x;
		windowSize.y = windowSize.y < style->windowMinSize.y ? style->windowMinSize.y : windowSize.y;

		// Node Content
		_currentGraph->_drawList->ChannelsSetCurrent(2);
		ImGui::SetCursorScreenPos(nodeWindowTopLeftCorner + style->windowPadding);
		ImGui::BeginGroup();
		ImGui::Text(node._name);
		ImGui::SetCursorScreenPos(contentPosition);

		int size = node._inputSlots.size() >= node._outputSlots.size() ? node._inputSlots.size() : node._outputSlots.size();
		for (int i = 0; i < size; i++)
		{
			if (i < node._inputSlots.size())
			{
				ImGui::SetCursorScreenPos(ImGui::GetCursorScreenPos() + ImVec2(style->slotOffset, 0.0f));
				ImGui::Text(node._inputSlots[i]._name);
				ImVec2 center = ImVec2(nodeWindowTopLeftCorner.x + style->slotOffset, ImGui::GetCursorScreenPos().y - ImGui::CalcTextSize(node._inputSlots[i]._name).y + ImGui::GetStyle().ItemSpacing.y);
				DrawSlot(center, node._inputSlots[i]);
			}
			if (i < node._outputSlots.size())
			{
				ImVec2 offset(windowSize.x - ImGui::CalcTextSize(node._outputSlots[i]._name).x - style->windowPadding.x - style->windowPadding.x - style->slotOffset, 0.0f);
				if (i < node._inputSlots.size())
					ImGui::SameLine(offset.x);
				else
					ImGui::SetCursorScreenPos(ImGui::GetCursorScreenPos() + offset);
				ImGui::Text(node._outputSlots[i]._name);

				ImVec2 center = ImVec2(nodeWindowTopLeftCorner.x + windowSize.x - style->slotOffset, ImGui::GetCursorScreenPos().y - ImGui::CalcTextSize(node._outputSlots[i]._name).y + ImGui::GetStyle().ItemSpacing.y);
				DrawSlot(center, node._outputSlots[i]);
			}
		}
		ImGui::EndGroup();

		// Set the window size and make an invisible button the size of it to be possible to be interacted with (E.g hovered, clicked, dragged around)
		windowSize = ImVec2(node.CalcNodeWidth(), ImGui::GetItemRectSize().y) + style->windowPadding + style->windowPadding;
		windowSize.x = windowSize.x < style->windowMinSize.x ? style->windowMinSize.x : windowSize.x;
		windowSize.y = windowSize.y < style->windowMinSize.y ? style->windowMinSize.y : windowSize.y;
		ImVec2 headerSize = ImVec2(windowSize.x, headerTitleSize.y + style->windowPadding.y + style->headerPadding.y);
		ImVec2 nodeBoxBottomRightCorner = nodeWindowTopLeftCorner + windowSize;

		ImGui::SetCursorScreenPos(nodeWindowTopLeftCorner);
		ImGui::InvisibleButton("node", windowSize);

		if (ImGui::IsItemHovered())
			_currentGraph->_nodeHovered = &node;
		else if(&node == _currentGraph->_nodeHovered)
			_currentGraph->_nodeHovered = nullptr;

		bool isNodeSelected = ImGui::IsItemActive();
		if (isNodeSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			node._position = node._position + ImGui::GetIO().MouseDelta;

		// Node Box Header
		_currentGraph->_drawList->ChannelsSetCurrent(1);
		ImU32 headerBgColor = _currentGraph->_nodeHovered == &node || isNodeSelected ? colors->_headerBackgroundHovered : colors->_headerBackground;;
		_currentGraph->_drawList->AddRectFilled(nodeWindowTopLeftCorner, nodeWindowTopLeftCorner + headerSize, headerBgColor, style->windowCornerRadius, ImDrawFlags_RoundCornersTop);
		_currentGraph->_drawList->AddLine(ImVec2(nodeWindowTopLeftCorner.x, nodeWindowTopLeftCorner.y + headerSize.y), nodeWindowTopLeftCorner + headerSize, colors->_headerSeparator);

		// Node Box Background
		_currentGraph->_drawList->ChannelsSetCurrent(0);
		ImU32 nodeBgBackground = _currentGraph->_nodeHovered == &node || isNodeSelected ? colors->_backgroundHovered : colors->_background;
		_currentGraph->_drawList->AddRectFilled(nodeWindowTopLeftCorner, nodeBoxBottomRightCorner, nodeBgBackground, style->windowCornerRadius);

		//Outline
		_currentGraph->_drawList->ChannelsSetCurrent(1);
		ImU32 outlineColor = _currentGraph->_nodeHovered == &node || isNodeSelected ? colors->_outlineHovered : colors->_outline;
		_currentGraph->_drawList->AddRect(nodeWindowTopLeftCorner, nodeBoxBottomRightCorner, outlineColor, style->windowCornerRadius, 0, style->_outlinethickness);

		ImGui::PopID();
		_currentGraph->_drawList->ChannelsMerge();
	}

	void GraphContext::CreateLink(Slot& start, Slot& end)
	{
		Link link = Link(start._node, end._node, &start, &end);
		end._state = SlotState::Connected;
		start._state = SlotState::Connected;

		_currentGraph->_links.push_back(link);
	}

	void GraphContext::DrawLinks()
	{
		for (int i = 0; i < _currentGraph->_links.size(); i++)
		{
			GraphStyle* style = &_currentGraph->_style;
			GraphColors* colors = &_currentGraph->_colorsStyle;

			Link* link = &_currentGraph->_links[i];
			ImVec2 pos1 = link->_startSlot->_center;
			ImVec2 pos2 = link->_endSlot->_center;

			_currentGraph->_drawList->AddLine(pos1, pos2, colors->_linkColor, style->_linkThickness);
		}
	}

	void GraphContext::DrawSlot(const ImVec2& center, Slot& slot)
	{
		slot._center = center;
		GraphStyle* style = &_currentGraph->_style;
		GraphColors* colors = &_currentGraph->_colorsStyle;

		float r = style->slotRadius;
		ImGui::PushID(slot._id);
		ImGui::SetCursorScreenPos(ImVec2(center.x - r, center.y - r));
		ImGui::InvisibleButton("s", ImVec2(r * 2.0f, r * 2.0f));

		bool isSlotSelected = ImGui::IsItemActive();
		if (isSlotSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		{
			switch (slot._state)
			{
				case Phantom::Empty:
					_currentGraph->_currentSlot = &slot;
					slot._state = SlotState::Connecting;
					break;
				case Phantom::Connecting:
					_currentGraph->_drawList->AddLine(center, ImGui::GetMousePos(), colors->_linkColor, style->_linkThickness);
					//_currentGraph->_drawList->AddBezierCurve(center, center + ImVec2(+50, 0), ImGui::GetMousePos() + ImVec2(-50, 0), ImGui::GetMousePos(), colors->_linkColor, style->_linkThickness);
					break;
				case Phantom::Connected:
					break;
				default:
					break;
			}
		}
		else if (&slot == _currentGraph->_currentSlot && slot._state != SlotState::Connecting)
		{
			_currentGraph->_currentSlot = nullptr;
			slot._state = SlotState::Empty;
		}

		bool hovered = false;
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly))
		{
			hovered = true;
			if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
				if (_currentGraph->_currentSlot && (_currentGraph->_currentSlot->_type != slot._type) && _currentGraph->_currentSlot->_state == SlotState::Connecting && slot._state != Connected && _currentGraph->_currentSlot->_node != slot._node)
					CreateLink(*_currentGraph->_currentSlot, slot);
				else if (_currentGraph->_currentSlot)
					_currentGraph->_currentSlot->_state = SlotState::Empty;
		}
		else
			hovered = false;

		ImU32 slotColor = hovered || isSlotSelected ? colors->_slotHovered : colors->_slot;
		_currentGraph->_drawList->AddCircle(center, style->slotRadius, slotColor);
		ImGui::PopID();
	}
}
