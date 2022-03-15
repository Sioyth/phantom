#include "SceneManager.h"

namespace Phantom
{
	Scene* SceneManager::_activeScene = nullptr;
	std::map<std::string, Scene*> SceneManager::_scenes = std::map<std::string, Scene*>();

	void SceneManager::ChangeScene(const std::string& name)
	{
		_activeScene = _scenes[name];
	}

	void SceneManager::AddScene(const std::string& name, Scene* scene)
	{
		_scenes.emplace(name, scene);
		if(!_activeScene)
			_activeScene = _scenes[name];
	}
}
