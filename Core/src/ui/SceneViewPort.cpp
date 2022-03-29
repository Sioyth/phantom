#include "SceneViewPort.h"
#include <imgui/imgui.h>
#include <iostream>

namespace Phantom
{
	FrameBuffer SceneViewPort::_sceneBuffer;
	glm::vec2 SceneViewPort::_viewPortSize;

	void SceneViewPort::Init()
	{
		_sceneBuffer.Create(800, 600);
	}

	void SceneViewPort::Render()
	{
		//ImGui::SetWindowSize(ImVec2(200, 200));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		static bool x = false;
		ImGui::Begin("Scene ViewPort", &x);
		ImVec2 imvpSize = ImGui::GetContentRegionAvail();
		glm::vec2 newViewPortSize = { imvpSize.x, imvpSize.y };

		ImGui::Image((void*)_sceneBuffer.Texture(), imvpSize, ImVec2(0, 1), ImVec2(1, 0));
		if (newViewPortSize != _viewPortSize)
		{
			_viewPortSize = newViewPortSize;
			//Renderer::Instance().ColorFrameBuffer().Resize(currentViewPortSize.x, currentViewPortSize.y);
			//std::cout << "Resize" << std::endl;
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
