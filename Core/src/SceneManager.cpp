#include "SceneManager.h"

namespace Phantom
{
	SceneManager* SceneManager::_instance = nullptr;

	Phantom::SceneManager::SceneManager()
	{
		if (_instance)
			_instance = this;
		else
			return;

		_activeScene = nullptr;
	}
}
