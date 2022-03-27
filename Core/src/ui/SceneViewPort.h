#ifndef SCENEVIEWPORT_H
#define SCENEVIEWPORT_H
#include <glm/glm.hpp>
#include "../render/FrameBuffer.h"
namespace Phantom
{
	class SceneViewPort
	{
		public:
			
			static void Init();
			static void Render();
			static inline void BindFrameBuffer() { _sceneBuffer.Bind(); };
			static inline void  UnbindFrameBuffer() { _sceneBuffer.Unbind(); };

		private:
			static glm::vec2 _viewPortSize;
			static FrameBuffer _sceneBuffer;
	};
}

#endif