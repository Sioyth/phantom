#ifndef EDITORCAMERA_H
#define EDITORCAMERA_H
#include <glm/glm.hpp>

namespace Phantom {

	class EditorCamera
	{
		public:
			EditorCamera(float aspect = 800.0f/600.0f, float fov = 50.0f);
			inline const glm::vec3& position() { return _position; };
			inline const glm::vec3& forward() { return _forward; };

			void Translate(const glm::vec3& translation);
			inline void SetAspect(float aspect) { _aspect = aspect; };
			inline void SetForward(const glm::vec3& forward) { _forward = forward; };

			const glm::mat4& Proj();
			const glm::mat4& View();

			void Update(const float& dt);

		private:

			void UpdateDirs();

			float _fov;
			float _speed;
			float _aspect;
			glm::vec3 _up;
			glm::vec3 _right;
			glm::vec3 _forward;
			glm::vec3 _position;

			glm::mat4 _proj;
			glm::mat4 _view;
	};
}
#endif