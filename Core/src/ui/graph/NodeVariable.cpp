#include "NodeVariable.h"

namespace Phantom
{
	NodeVariable::NodeVariable(const char* name, unsigned int id, ImVec2 pos, DataType dataType) : Node(id, pos)
	{
		_id = id;
		_position = pos;
		_name = name;
		_type = NodeType::Variable;
		AddSlot("", SlotType::Output, dataType);
	}
	NodeVariable::NodeVariable(const char* name, unsigned int id, ImVec2 pos, void* data, bool constant, DataType dataType)
	{
		_id = id;
		_position = pos;
		_name = name;
		_type = NodeType::Variable;
		AddSlot("", SlotType::Output, dataType);

		_outputSlots[0]._data->SetData(std::shared_ptr<void>(data));
		_constant = constant;
	}
}