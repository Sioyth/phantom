#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
namespace Phantom 
{
	struct Transform
	{
		public:
	
			Transform();
			Transform(const Transform& other);

			void Scale(const glm::vec3& scale);
			void Rotate(const glm::vec3& rotation);
			void Translate(const glm::vec3& translation);

			const glm::vec3& up();
			const glm::vec3& right();
			const glm::vec3& forward();
			inline const glm::vec3& scale() { return _scale; };
			inline const glm::mat4& matrix() { return _matrix; };
			inline const glm::vec3& rotation() { return _rotation; };
			inline const glm::vec3& position() { return _position; };

		private:
			glm::vec3 _scale;
			glm::mat4 _matrix;
			glm::vec3 _position;
			glm::vec3 _rotation;
	};
}
#endif
