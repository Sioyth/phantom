#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <map>
#include "Scene.h"
namespace Phantom
{
	class SceneManager
	{
		public:
			inline static Scene* ActiveScene() { return _activeScene; };
			static void ChangeScene(const std::string& name);
			static void AddScene(const std::string& name, Scene* scene = new Scene());
		private:
			static Scene* _activeScene;
			static std::map<std::string, Scene*> _scenes;
	};
}

#endif

