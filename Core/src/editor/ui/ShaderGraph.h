#ifndef SHADERGRAPH_H
#define SHADERGRAPH_H

#include <list>
#include <string>
#include <vector>
#include <imgui/imgui_internal.h> 
namespace Phantom 
{
	//struct EmptyBranch {};
	//struct Node
	//{
	//	unsigned int _id;
	//	std::string _name;
	//	ImVec2 _position; 
	//	//std::vector<Slot> _slots;
	//	Node(std::string name, unsigned int id, ImVec2 position) : _name(name) , _position(position), _id(id) {};
	//};

	//enum PortType { Input, Output };
	//enum class ValueType { FLOAT = 1, VEC2, VEC3, VEC4, SAMPLER2D, INVALID = 0 };
	//template < typename T>
	//struct Port
	//{
	//	T _value;
	//	PortType _type;
	//	ValueType _valueType;
	//	//Branch(BranchType type) : _type(type) {};
	//};

	class ShaderGraph
	{
		public:
			static void Render();
		private:
			static void DrawGrid();
			//static void DrawNode(Node& node);

			static ImVec2 _offset;
			static ImVec2 _mouseDrag;
			//static Node* _nodeHovered;
			static ImDrawList* _drawList;
			//static std::list<Node> _nodes;

	};
}
#endif

