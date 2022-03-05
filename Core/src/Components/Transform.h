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

	inline glm::vec3 GetPosition() { return _position; };
	inline glm::mat4x4 GetMatrix() { return _transformMatrix; };
	
	virtual void Update();

	private:
		glm::vec3 _scale;
		glm::vec3 _rotation;
		glm::vec3 _position; // change too coordinates?
		glm::mat4x4 _transformMatrix;
};

#endif

