#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <map>
#include "Scene.h"
namespace Phantom
{
	class SceneManager
	{
		public:
			static Scene* CurrentScene();
			static void ChangeScene(const std::string& name);
			static void AddScene(const std::string& name, Scene* scene = new Scene());
		private:
			static Scene* _currentScene;
			static std::map<std::string, Scene*> _scenes;
	};
}

#endif

