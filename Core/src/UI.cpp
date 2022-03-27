#include "UI.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "scene/Entity.h"
#include "scene/SceneManager.h"

#include <iostream>

namespace Phantom
{
	bool UI::Init(GLFWwindow& window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		if (!ImGui_ImplGlfw_InitForOpenGL(&window, true))
			return false;
		if (!ImGui_ImplOpenGL3_Init())
			return false;

		ImGui::StyleColorsDark();

		// Enable Docking
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		return true;
	}

	void UI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}

	void UI::EndFrame()
	{
		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UI::ShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

