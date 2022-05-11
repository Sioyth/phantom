#ifndef NODE_H
#define NODE_H
#include <vector>
#include <imgui/imgui_internal.h>
#include <glm/glm.hpp>

namespace Phantom
{
	class Node;
	class GraphContext;

	enum SlotState{ Empty = 0, Connecting, Connected };
	enum SlotType{Input = 0, Output};

	struct Slot
	{
		glm::vec3 _data;
		const char* _name;
		unsigned int _id;
		Node* _node;
		Slot* _linkedSlot;

		ImVec2 _center;
		SlotType _type;
		SlotState _state = SlotState::Empty;

		Slot() = default;
		Slot(const char* name, unsigned int id, Node* node, SlotType type) : _name(name) , _id(id), _node(node), _type(type) {};
	};

	struct Link
	{
		glm::vec3 _data;
		Node* _startNode;
		Node* _endNode;
		Slot* _startSlot;
		Slot* _endSlot; // Target?

		Link(Node* startNode, Node* endNode, Slot* startSlot, Slot* endSlot) : _startNode(startNode), _endNode(endNode), _startSlot(startSlot), _endSlot(endSlot) {}
	};

	enum NodeType { Core = 0, Variable, Custom};

	class Node
	{
		public:
			Node() = default;
			Node(unsigned int id, ImVec2 pos);
			void AddSlot(const char* name, SlotType type);
			virtual void Resolve();

			inline const char* Name() { return _name; };
		protected:
			float _width;
			bool _constant;
			NodeType _type;
			ImVec2 _position;
			unsigned int _id;
			unsigned int _guid = 0;
			bool _resolved = false;
			const char* _name = "Node";

			std::vector<Slot> _inputSlots;
			std::vector<Slot> _outputSlots;

			float CalcNodeWidth();

			friend class GraphContext;
	};
}

#endif

