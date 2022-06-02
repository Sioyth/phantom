#ifndef NODE_H
#define NODE_H
#include <vector>
#include <imgui/imgui_internal.h>
#include <glm/glm.hpp>
#include "UniformValue.h"

namespace Phantom
{
	class Node;
	class GraphContext;
	class Graph;

	enum SlotState{ Empty = 0, Connecting, Connected };
	enum SlotType{Input = 0, Output};

	struct Slot
	{
		UniformValue* _data;
		const char* _name;
		unsigned int _id;
		Node* _node;
		Slot* _linkedSlot;

		ImVec2 _center;
		SlotType _type;
		SlotState _state = SlotState::Empty;

		Slot() = default;
		Slot(const char* name, unsigned int id, Node* node, SlotType type, DataType datatype) : _name(name) , _id(id), _node(node), _type(type) 
		{
			_data = new UniformValue();
			_data->SetDataType(datatype);
		};
	};

	struct Link
	{
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
			void AddSlot(const char* name, SlotType type, DataType dataType = DataType::All);
			virtual void Resolve();
			inline unsigned int GetID() { return _id; }

			inline const char* Name() { return _name; };
		protected:
			float _width;
			bool _constant;
			Graph* _graph; // Change to a better name
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

