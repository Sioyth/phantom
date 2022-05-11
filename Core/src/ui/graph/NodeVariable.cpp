#include "NodeVariable.h"

namespace Phantom
{
	NodeVariable::NodeVariable(const char* name, unsigned int id, ImVec2 pos) : Node(id, pos)
	{
		_id = id;
		_position = pos;
		_name = name;
		_type = NodeType::Variable;
		AddSlot("", SlotType::Output);
	}
}