#include "EditorLayer.h"
#include "scene/SceneManager.h"
#include "render/Renderer.h"

namespace Phantom
{
	EditorLayer* EditorLayer::_instance = nullptr;

	void EditorLayer::Update(const float& dt)
	{
		_editorCamera.Update(dt);
		Renderer::Instance().Draw(*SceneManager::ActiveScene());
	}

	EditorLayer* EditorLayer::Instance()
	{
		return _instance;
	}
}
