#ifndef RENDERER_H
#define RENDERER_H
#include "Component.h"
#include "../Shader/Material.h"

class Renderer : public Component
{
	public:
		Renderer(Entity* entity) : Component(entity) {};
		virtual void Update();
	private:
		Material _material;

};

#endif 

