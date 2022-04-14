#ifndef SHADERGRAPH_H
#define SHADERGRAPH_H

#include <list>
#include <string>
#include <vector>
#include <imgui/imgui_internal.h> 
#include "../../ui/graph/Graph.h"

namespace Phantom 
{
	class ShaderGraph
	{
		public:
			static void Draw();
		private:
			static void ContextMenu();
			static GraphContext _graphContext;
	};
}
#endif

