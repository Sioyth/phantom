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
		unsigned int _data;
	};

	class Node
	{
		public:
			Node(unsigned int id, ImVec2 pos);
			//virtual void Resolve() = 0;
		protected:
			const char* _name = "test";
			unsigned int _id;
			ImVec2 _position;
			float _width;

			std::vector<Slot> _inputSlots;
			std::vector<Slot> _outputSlots;

			float CalcNodeWidth();

			friend class GraphContext;
	};
}

#endif

