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
		SceneViewPort::Init(800, 600);
		_editorCamera.Translate(glm::vec3(0.0f, 1.0f, 10.0f));
	}

	void EditorLayer::Update(const float& dt)
	{
		_editorCamera.Update(dt);

		SceneViewPort::BindFrameBuffer();
		Renderer::Instance()->Render(*SceneManager::CurrentScene(), _editorCamera, SceneViewPort::GetAspectRatio());
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
