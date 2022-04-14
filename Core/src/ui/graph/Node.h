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
		int _data;
		const char* _name;
		unsigned int _id;
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
		Slot* _startSlot;
		Slot* _endSlot; // Target?

		Link(Node* startNode, Node* endNode, Slot* startSlot, Slot* endSlot) : _startNode(startNode), _endNode(endNode), _startSlot(startSlot), _endSlot(endSlot) {}
	};

	class Variable
	{
		public:
			Variable() { _outSlot._type = SlotType::Output; };
			inline const char* Name() { return _name; };
			inline const unsigned int Id() { return _id; };
		private:
			Slot _outSlot;
			const char* _name;
			unsigned int _id;
			ImVec2 _position;

			friend class GraphContext;
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

