#include "EditorLayer.h"
#include "scene/SceneManager.h"
#include "render/Renderer.h"

#include "ui/SceneHierarchy.h"
#include "ui/SceneViewPort.h"
#include "UI.h"

namespace Phantom
{
	EditorLayer* EditorLayer::_instance = nullptr;

	EditorLayer::EditorLayer()
	{
		SceneViewPort::Init();
	}

	void EditorLayer::Update(const float& dt)
	{
		_editorCamera.Update(dt);

		SceneViewPort::BindFrameBuffer();
		Renderer::Instance()->Render(*SceneManager::CurrentScene(), _editorCamera);
		SceneViewPort::UnbindFrameBuffer();

		// ui
		UI::NewFrame();
		SceneViewPort::Render();
		SceneHierarchy::Render();
		UI::EndFrame();
	}

	EditorLayer* EditorLayer::Instance()
	{
		if (_instance == nullptr)
			_instance = new EditorLayer();
		return _instance;
	}
}
