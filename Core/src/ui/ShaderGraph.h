#ifndef SHADERGRAPH_H
#define SHADERGRAPH_H

#include <vector>
#include <string>
namespace Phantom 
{
	struct EmptyBranch {};
	struct Node
	{
		std::string _name;
		unsigned int _id;
		//std::vector<Branch<Node, int>> _branches;
		Node(std::string name) : _name(name) {};
	};


	enum BranchType { Input, Output };
	template <typename Node, typename T>
	struct Branch
	{
		T _value;
		Node* _target;
		BranchType _type;
		//Branch(BranchType type) : _type(type) {};
	};

	class ShaderGraph
	{
		public:
			static void Render();
		private:
			static std::vector<Node> _nodes;

	};
}
#endif

