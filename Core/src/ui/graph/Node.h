#ifndef NODE_H
#define NODE_H
#include <vector>
#include <imgui/imgui_internal.h>

namespace Phantom
{

	struct Link
	{
		int _data;
		unsigned int _inputNodeId;
		unsigned int _outputNodeId;
	};

	struct Slot
	{
		const char* _name;
		unsigned int _id;
		unsigned int _data;
		Slot() = default;
		Slot(const char* name, unsigned int id) : _name(name) , _id(id) {};
	};

	enum SlotType { In, Out};

	class Node
	{
		public:
			Node(unsigned int id, ImVec2 pos);
			void AddSlot(const char* name, SlotType type);
			//virtual void Resolve() = 0;
		protected:
			const char* _name = "test";
			unsigned int _id;
			unsigned int _guid;
			ImVec2 _position;
			float _width;

			std::vector<Slot> _inputSlots;
			std::vector<Slot> _outputSlots;

			float CalcNodeWidth();

			friend class GraphContext;
	};
}

#endif

