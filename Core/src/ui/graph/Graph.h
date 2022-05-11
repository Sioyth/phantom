#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <map>
#include "Node.h"
#include "NodeVariable.h"

namespace Phantom
{
	// VERY TEMP;
	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

	enum GraphFlags { None = 0, NoGrid};

	struct GraphStyle
	{
		float gridSize = 32.0f;

		float _outlinethickness = 1.0f;

		float windowCornerRadius = 4.0f;
		ImVec2 windowPadding = ImVec2(10.0f, 8.0f);
		ImVec2 windowMinSize = ImVec2(150.0f, 50.0f);

		ImVec4 headerPadding = ImVec4(10.0f, 5.0f, 0.0f, 0.0f); // Bottom - Top - Left - Right padding

		ImColor _linkThickness = 3.0f;

		float slotRadius = 4.0f;
		float slotOffset = 10.0f;

		GraphStyle() {};
	};

	struct GraphColors
	{
		ImColor _grid = IM_COL32(200, 200, 200, 40);

		ImColor _outline= IM_COL32(100, 100, 100, 255);
		ImColor _outlineHovered = IM_COL32(100, 255, 100, 255);

		ImColor _background = IM_COL32(60, 60, 60, 255);
		ImColor _backgroundHovered = IM_COL32(50, 50, 50, 255);

		ImColor _headerBackground = IM_COL32(60, 90, 60, 255);
		ImColor _headerSeparator = IM_COL32(100, 100, 100, 255);
		ImColor _headerBackgroundHovered = ImColor(60, 80, 60, 255);

		ImColor _linkColor = ImColor(200, 80, 60, 255);

		ImColor _slot = IM_COL32(255, 80, 60, 255);
		ImColor _slotHovered = IM_COL32(255, 255, 60, 255);
		ImColor _slotFilled;

		GraphColors() {};
	};

	struct Graph
	{
		ImVec2 _offset;
		ImVec2 _mouseDrag;
		Node* _nodeHovered;
		Node* _variableHovered;
		Slot* _currentSlot;
		ImDrawList* _drawList;
		std::list<Node*> _nodes;
		std::list <Link> _links;
		std::list<NodeVariable*> _variables;

		GraphStyle _style;
		GraphColors _colorsStyle;
	};

	class GraphContext
	{
		public:
			GraphContext();

			void EndGraph();
			void DeleteNode(Node* node);
			void CreateNode(Node* node, const ImVec2& pos);
			void CreateVariable(const char* name);
			void CreateVariableOnGraph(NodeVariable* variable);
			void BeginGraph(const char* name, GraphFlags flags = None);

			inline const ImVec2& GetGraphPosition() { return ImGui::GetMousePosOnOpeningCurrentPopup() - _currentGraph->_offset; };

			/*inline Style& GetStyle() { return _currentGraph->_style; };
			inline ColorsStyle& GetColorsStyle() { return _currentGraph->_colorsStyle; };*/
			inline Graph* GetGraph() { return _currentGraph; }
		private:
			// Move to Graph
			void DrawGrid();
			void DrawLinks(Link& link);
			void DrawNodeWindow(Node& node);
			void DrawVariables(Node& var);
			void DrawSlot(const ImVec2& center, Slot& slot);
			
			void Resolve();
			void CreateLink(Slot& start, Slot& end);

			unsigned int _guid;
			Graph* _currentGraph;
			std::map<const char*, Graph> _graphs;
	};
}

#endif

