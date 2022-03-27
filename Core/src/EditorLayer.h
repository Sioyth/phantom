#ifndef EDITORLAYER_H
#define EDITORLAYER_H
#include "scene/EditorCamera.h"

namespace Phantom 
{
	class EditorLayer
	{
		public:
			void Update(const float& dt);
			static EditorLayer* Instance();
		private:
			EditorCamera _editorCamera;
			static EditorLayer* _instance;
	};
}

#endif

