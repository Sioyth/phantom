#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <map>
#include "Node.h"

namespace Phantom
{

	enum GraphFlags { None = 0, NoGrid};

	struct Style
	{
		float gridSize = 32.0f;

		float windowCornerRadius = 4.0f;
		ImVec2 windowPadding = ImVec2(10.0f, 8.0f);
		ImVec2 windowMinSize = ImVec2(150.0f, 50.0f);

		ImVec4 headerPadding = ImVec4(10.0f, 5.0f, 0.0f, 0.0f); // Bottom - Top - Left - Right padding

		float slotRadius = 4.0f;
		float slotOffset = 10.0f;

		Style() {};
	};

	struct ColorsStyle
	{
		ImColor _outline= IM_COL32(100, 100, 100, 255);
		ImColor _outlineHovered = IM_COL32(100, 255, 100, 255);

		ImColor _background = IM_COL32(60, 60, 60, 255);
		ImColor _backgroundHovered = IM_COL32(50, 50, 50, 255);

		ImColor _headerBackground = IM_COL32(60, 90, 60, 255);
		ImColor _headerSeparator = IM_COL32(100, 100, 100, 255);
		ImColor _headerBackgroundHovered = ImColor(60, 80, 60, 255);

		ImColor _slot = IM_COL32(255, 80, 60, 255);
		ImColor _slotHovered = IM_COL32(255, 255, 60, 255);
		ImColor _slotFilled;

		ColorsStyle() {};
	};

	struct Graph
	{
		ImVec2 _offset;
		ImVec2 _mouseDrag;
		Node* _nodeHovered;
		ImDrawList* _drawList;
		std::list<Node> _nodes;
		std::vector <Link> _links;

		Style _style;
		ColorsStyle _colorsStyle;
	};

	class GraphContext
	{
		public:
			GraphContext();

			void EndGraph();
			void CreateNode(const char* name, const ImVec2& pos);
			void BeginGraph(const char* name, GraphFlags flags = None);

			/*inline Style& GetStyle() { return _currentGraph->_style; };
			inline ColorsStyle& GetColorsStyle() { return _currentGraph->_colorsStyle; };*/
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

