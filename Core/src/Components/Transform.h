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

	inline const glm::vec3& Position() { return _position; };
	inline const glm::mat4x4& Matrix() { return _transformMatrix; };

	const glm::vec3& Up();
	const glm::vec3& Right();
	const glm::vec3& Forward();
	
	virtual void Update();

	private:

		glm::vec3 _scale;
		glm::vec3 _rotation;
		glm::vec3 _position; // change too coordinates?

		glm::vec3 _up;
		glm::vec3 _right;
		glm::vec3 _forward;

		// find better name
		void UpdateOrientation();

		glm::mat4x4 _transformMatrix;
};

#endif

