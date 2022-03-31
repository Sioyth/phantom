#include "SceneViewPort.h"
#include <imgui/imgui.h>
#include <iostream>

namespace Phantom
{
	float SceneViewPort::_aspectRatio;
	glm::vec2 SceneViewPort::_viewPortSize;
	FrameBuffer SceneViewPort::_sceneBuffer;

	void SceneViewPort::Init(const float& width, const float& height)
	{
		Init(glm::vec2(width, height));
	}

	void SceneViewPort::Init(const glm::vec2& viewPortSize)
	{
		_viewPortSize = viewPortSize;
		_sceneBuffer.Create(_viewPortSize.x, _viewPortSize.y);
		_aspectRatio = (float)_viewPortSize.x / (float)_viewPortSize.y;
		std::cout << "Aspect Ratio: " << _aspectRatio << std::endl;
	}

	void SceneViewPort::Render()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(_viewPortSize.x, _viewPortSize.y), ImGuiCond_FirstUseEver);
		ImGui::Begin("Scene ViewPort");

			ImVec2 imvpSize = ImGui::GetContentRegionAvail();
			glm::vec2 newViewPortSize = { imvpSize.x, imvpSize.y };
			ImGui::Image((void*)_sceneBuffer.Texture(), imvpSize, ImVec2(0, 1), ImVec2(1, 0));
			if (newViewPortSize != _viewPortSize)
			{
				_viewPortSize = newViewPortSize;
				_sceneBuffer.Resize(_viewPortSize);
				_aspectRatio = (float)_viewPortSize.x / (float)_viewPortSize.y;
			}

		ImGui::End();
		ImGui::PopStyleVar();
	}
}
