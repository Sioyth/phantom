#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Scene.h"
#include <map>
namespace Phantom
{
	class SceneManager
	{
		public:
			SceneManager();
			//void AddScene(std::string name, const Scene& scene);
		private:
			Scene* _activeScene;
			//std::map<std::string, Scene> _scenes;
			static SceneManager* _instance;
	};
}

#endif

