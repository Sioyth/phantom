#ifndef NODE_H
#define NODE_H
#include <vector>
#include <imgui/imgui_internal.h>

namespace Phantom
{

	class Node;

	enum SlotState{ Empty = 0, Connecting, Connected };
	enum SlotType{Input = 0, Output};

	struct Slot
	{
		const char* _name;
		unsigned int _id;
		unsigned int _data;
		Node* _node;

		ImVec2 _center;
		SlotType _type;
		SlotState _state = SlotState::Empty;

		Slot() = default;
		Slot(const char* name, unsigned int id, Node* node, SlotType type) : _name(name) , _id(id), _node(node), _type(type) {};
	};

	struct Link
	{
		int _data;
		Node* _startNode;
		Node* _endNode;
		Slot* _slotStart;
		Slot* _slotEnd;
	};

	class Node
	{
		public:
			Node(unsigned int id, ImVec2 pos);
			void AddSlot(const char* name, SlotType type);
			//virtual void Resolve() = 0;
		protected:
			const char* _name = "test";
			unsigned int _id;
			unsigned int _guid = 0;
			ImVec2 _position;
			float _width;

			std::vector<Slot> _inputSlots;
			std::vector<Slot> _outputSlots;

			float CalcNodeWidth();

			friend class GraphContext;
	};
}

#endif

