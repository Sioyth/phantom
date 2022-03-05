#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"

class Camera : public Component
{
public:
	Camera(Entity* entity);
	virtual void Update() {};

	inline static Camera* GetMainCamera() { return _mainCamera; };
		void SetMainCamera();
	private:
		static Camera* _mainCamera;
	
};

#endif 

