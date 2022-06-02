#ifndef NODEVARIABLE_H
#define NODEVARIABLE_H
#include "Node.h"

namespace Phantom
{
	class NodeVariable : public Node
	{
	public:
		NodeVariable(const char* name, unsigned int id, ImVec2 pos, DataType dataType = DataType::All);
		NodeVariable(const char* name, unsigned int id, ImVec2 pos, void* data, bool constant, DataType dataType);
		inline void SetConstant(bool c) { _constant = c; };
		inline const bool& GetConstant() { return _constant; };
		private:
			bool _constant;
			virtual void Resolve() { };
	};
}

#endif 

