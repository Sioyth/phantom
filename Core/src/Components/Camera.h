#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"

//Camera* Camera::_mainCamera = nullptr;

class Camera : public Component
{
	public:
		Camera(Entity* entity);
		virtual void Update() {};

		static Camera* GetMainCamera();
		void SetMainCamera();
	private:
		static Camera* _mainCamera;
	
};

#endif 

