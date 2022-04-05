#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <map>
#include "Node.h"

namespace Phantom
{

	enum GraphFlags { None = 0, NoGrid};

	struct Graph
	{
		ImVec2 _offset;
		ImVec2 _mouseDrag;
		Node* _nodeHovered;
		ImDrawList* _drawList;
		std::list<Node> _nodes;
	};
	
	class GraphContext
	{
		public:
			GraphContext();

			void BeginGraph(const char* name, GraphFlags flags = None);
			void EndGraph();
		private:
			void DrawGrid(const char* name);
			void DrawNode(Graph* graph, Node& node);

			std::map<const char*, Graph> _graphs;
	};
}

#endif

