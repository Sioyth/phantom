#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include <glm/glm.hpp>

class Camera : public Component
{
public:
	Camera(Entity* entity);
	virtual void Update();

	void SetMainCamera();
	const glm::mat4x4& ViewMatrix();
	inline static Camera* GetMainCamera() { return _mainCamera; };
	private:
		glm::vec3 _lastPos;
		glm::mat4 _viewMatrix;
		static Camera* _mainCamera;
	
};

#endif 

