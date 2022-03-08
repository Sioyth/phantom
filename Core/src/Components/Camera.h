#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include <glm/glm.hpp>

namespace Phantom
{
	class Camera
	{
		public:
			Camera();
			const glm::mat4x4& ViewMatrix();
			void SetPerspective();

		private:
			glm::mat4 _viewMatrix;
			glm::mat4 _projectionMatrix;
	};
}

#endif 

