#ifndef SCENEVIEWPORT_H
#define SCENEVIEWPORT_H
#include <glm/vec2.hpp>
#include "../render/FrameBuffer.h"
namespace Phantom
{
	class SceneViewPort
	{
		public:
			
			static void Init(const float& width, const float& height);
			static void Init(const glm::vec2& viewPortSize);
			static void Render();
			static inline void BindFrameBuffer() { _sceneBuffer.Bind(); };
			static inline void  UnbindFrameBuffer() { _sceneBuffer.Unbind(); };
			static inline const glm::vec2& GetViewPortSize() { return _viewPortSize; };
			static inline const float& GetAspectRatio() { return _aspectRatio; };

		private:
			static float _aspectRatio;
			static glm::vec2 _viewPortSize;
			static FrameBuffer _sceneBuffer;
	};
}

#endif