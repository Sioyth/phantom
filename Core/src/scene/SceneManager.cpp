#include "SceneManager.h"

namespace Phantom
{
	Scene* SceneManager::_currentScene = nullptr;
	std::map<std::string, Scene*> SceneManager::_scenes = std::map<std::string, Scene*>();

	Scene* SceneManager::CurrentScene()
	{
		if (_currentScene == nullptr)
			_currentScene = new Scene(true);

		return _currentScene;
	}

	void SceneManager::ChangeScene(const std::string& name)
	{
		_currentScene = _scenes[name];
	}

	void SceneManager::AddScene(const std::string& name, Scene* scene)
	{
		_scenes.emplace(name, scene);
		if(!_currentScene)
			_currentScene = _scenes[name];
	}
}
