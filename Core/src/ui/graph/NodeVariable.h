#ifndef NODEVARIABLE_H
#define NODEVARIABLE_H
#include "Node.h"

namespace Phantom
{
	class NodeVariable : public Node
	{
		public:
			NodeVariable(const char* name, unsigned int id, ImVec2 pos);
		private:
			virtual void Resolve() { };
	};
}

#endif 

