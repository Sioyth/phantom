#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
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
		std::vector <Link> _links;

		//Style _style;
	};

	struct Style 
	{
		float gridSize = 32.0f;

		float windowCornerRadius;
		ImVec2 windowPadding = ImVec2(10.0f, 8.0f);
		ImVec2 windowMinSize = ImVec2(150.0f, 50.0f);

		ImVec4 headerPadding = ImVec4(10.0f, 5.0f, 0.0f, 0.0f);

		float slotRadius;
		
		Style();
	};

	struct Colors
	{
		
		Colors();
	};
	
	class GraphContext
	{
		public:
			GraphContext();

			void EndGraph();
			void CreateNode(const char* name, const ImVec2& pos);
			void BeginGraph(const char* name, GraphFlags flags = None);
		private:
			void DrawLinks();
			void DrawGrid(const char* name);
			void DrawSlot(const ImVec2& center);
			void DrawNodeWindow(Node& node);

			unsigned int _guid;
			Graph* _currentGraph;
			std::map<const char*, Graph> _graphs;
	};
}

#endif

