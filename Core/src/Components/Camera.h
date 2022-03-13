#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "Transform.h"

namespace Phantom
{

	enum class CameraProjection
	{
		Perspective = 0, Ortographic
	};

	struct Camera
	{
	public:
		Camera();
		inline const glm::mat4& proj() { return _proj; }
		inline const glm::mat4& view() { return _view; }

		void CalculateMatrices(Transform& transform);

	private:
		float _fov;
		glm::mat4 _proj;
		glm::mat4 _view;
		glm::vec2 _clippingPlanes; // near fars
		CameraProjection _projection;


	};
}

#endif // !CAMERA_H

