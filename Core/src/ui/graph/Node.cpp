#include "Node.h"

namespace Phantom
{
	Node::Node(unsigned int id, ImVec2 pos)
	{
		_id = id;
		_position = pos;
	}

	void Node::AddSlot(const char* name, SlotType type)
	{
		switch (type)
		{
		case Input:
			_inputSlots.push_back(Slot(name, _guid, this, Input));
			break;
		case Output:
			_outputSlots.push_back(Slot(name ,_guid, this, Output));
			break;
		default:
			break;
		}

		_guid++;
	}

	void Node::Resolve()
	{
		for (int i = 0; i < _inputSlots.size(); i++)
		{
			if (_inputSlots[i]._state == SlotState::Connected && _inputSlots[i]._linkedSlot->_node->_resolved == false)
			{
				_inputSlots[i]._linkedSlot->_node->Resolve();
				_inputSlots[i]._data = _inputSlots[i]._linkedSlot->_data;
			}
				else
					continue;
		}
	}

	float Node::CalcNodeWidth()
	{
		float inputWidth = 0;
		float outputWidth = 0;

		for (int i = 0; i < _inputSlots.size(); i++)
		{
			float tempInWidth = ImGui::CalcTextSize(_inputSlots[i]._name).x;
			if (tempInWidth > inputWidth)
				inputWidth = tempInWidth;

			if (i < _outputSlots.size())
			{
				float tempOutWidth = ImGui::CalcTextSize(_outputSlots[i]._name).x;
				if (tempOutWidth > outputWidth)
					outputWidth = tempOutWidth;
			}
		}

		_width = inputWidth + outputWidth;
		return _width + ImGui::GetStyle().ItemSpacing.x;
	}
}
