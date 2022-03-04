#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include "Component.h"
class Transform : public Component
{
	public:
		Transform(Entity* entity);
		//Transform();

		void Scale(glm::vec3 scale);
		void Rotate(glm::vec3 rotation);
		void Translate(glm::vec3 translation);

		virtual void Update();

	private:
		glm::vec3 _scale;
		glm::vec3 _rotation;
		glm::vec3 _position;
		glm::mat4x4 _transformMatrix;
};

#endif

