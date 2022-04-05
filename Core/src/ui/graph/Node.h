#ifndef NODE_H
#define NODE_H
#include <string>
#include <imgui/imgui_internal.h>

namespace Phantom
{
	class Node
	{
		public:
			Node(ImVec2 pos) : _position(pos) {};
			//virtual void Resolve() = 0;
		private:
			unsigned int _id;
			std::string _name;
			ImVec2 _position;

			friend class GraphContext;
	};
}

#endif

