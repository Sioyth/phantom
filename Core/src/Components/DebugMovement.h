#ifndef DEBUGMOVEMENT_H
#define DEBUGMOVEMENT_H
#include "Component.h"

class DebugMovement : public Component
{
	public:
		virtual void Update();
	private:
		float speed = 0.1f;
};

#endif;
