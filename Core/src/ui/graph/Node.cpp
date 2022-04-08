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
		case Phantom::In:
			_inputSlots.push_back(Slot(name, _guid));
			break;
		case Phantom::Out:
			_outputSlots.push_back(Slot(name,_guid));
			break;
		default:
			break;
		}

		_guid++;
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
