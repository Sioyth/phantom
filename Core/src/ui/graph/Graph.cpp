#include "Graph.h"
#include <iostream>

namespace Phantom
{
	GraphContext::GraphContext()
	{

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

		for (std::list<Node*>::iterator node = _currentGraph->_nodes.begin(); node != _currentGraph->_nodes.end(); node++)
			DrawNodeWindow(**node);

		for (std::list<Link>::iterator link = _currentGraph->_links.begin(); link != _currentGraph->_links.end(); link++)
			DrawLinks(*link);

		// Mouse Drag
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
			_graphs[name]._mouseDrag = _graphs[name]._mouseDrag + ImGui::GetIO().MouseDelta;
	}

	void GraphContext::EndGraph()
	{
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void GraphContext::DeleteNode(Node* node)
	{
		_currentGraph->_nodes.remove(node);
		delete node;
	}

	void GraphContext::CreateNode(Node* node, const ImVec2& pos)
	{
		node->_id = _guid++;
		node->_position = pos;
		_currentGraph->_nodes.push_back(std::move(node));
	}

	void GraphContext::CreateVariable(const ImVec2& pos)
	{
		_currentGraph->_nodes.push_back(new NodeVariable(_guid++, pos));
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
		if (node._type == NodeType::Variable)
			DrawVariables(node);

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
		ImGui::InvisibleButton("node", windowSize, ImGuiButtonFlags_AllowItemOverlap);
		ImGui::SetItemAllowOverlap();

		if (ImGui::IsItemHovered() && (!_currentGraph->_nodeHovered || _currentGraph->_nodeHovered->_id < node._id))
			_currentGraph->_nodeHovered = &node;
		else if (!ImGui::IsItemHovered() && &node == _currentGraph->_nodeHovered)
			_currentGraph->_nodeHovered = nullptr;

		bool isNodeSelected = ImGui::IsItemActive() && &node == _currentGraph->_nodeHovered;
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

	void GraphContext::Resolve()
	{
		for (std::list<Node*>::iterator node = _currentGraph->_nodes.begin(); node != _currentGraph->_nodes.end(); node++)
			(*node)->Resolve();
	}

	void GraphContext::CreateLink(Slot& start, Slot& end)
	{
		Link link = Link(start._node, end._node, &start, &end);
		end._state = SlotState::Connected;
		start._state = SlotState::Connected;
		end._linkedSlot = &start;
		start._linkedSlot = &end;

		Resolve();
		_currentGraph->_links.push_back(link);
	}

	void GraphContext::DrawLinks(Link& link)
	{
		GraphStyle* style = &_currentGraph->_style;
		GraphColors* colors = &_currentGraph->_colorsStyle;
		_currentGraph->_drawList->AddLine(link._startSlot->_center, link._endSlot->_center, colors->_linkColor, style->_linkThickness);
	}

	void GraphContext::DrawVariables(Node& var)
	{
		GraphStyle* style = &_currentGraph->_style;
		GraphColors* colors = &_currentGraph->_colorsStyle;

		// Node Content
		ImGui::PushItemWidth(_currentGraph->_style.windowMinSize.x - style->windowPadding.x - style->windowPadding.x - style->slotOffset);

		ImGui::InputInt("", &var._outputSlots[0]._data, 0);
		ImGui::SameLine();
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
			if(slot._state != SlotState::Connected) 
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
