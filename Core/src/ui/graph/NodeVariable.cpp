#include "NodeVariable.h"

namespace Phantom
{
	NodeVariable::NodeVariable(unsigned int id, ImVec2 pos) : Node(id, pos)
	{
		_id = id;
		_position = pos;
		_type = NodeType::Variable;
		AddSlot("", SlotType::Output);
	}
}