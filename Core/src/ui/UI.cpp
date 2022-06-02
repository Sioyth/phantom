#include "UI.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

namespace Phantom
{
	bool UI::Init(GLFWwindow& window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Config
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		if (!ImGui_ImplGlfw_InitForOpenGL(&window, true))
			return false;
		if (!ImGui_ImplOpenGL3_Init())
			return false;

		ImGui::StyleColorsDark();

		SetDefaultTheme();
		return true;
	}

	void UI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); // If you take this out, the window isn't being cleared. possible bug?

		/*static bool demo = true;
		ImGui::ShowDemoWindow(&demo);*/
	}

	void UI::EndFrame()
	{
		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
	    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	    //  We could also call glfwMakeContextCurrent(_window) if we had acess to the glfw window)
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void UI::ShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::SetDefaultTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0;
		style.ChildBorderSize = 0;
		style.PopupBorderSize = 0;

		style.WindowRounding = 4;
		style.FrameRounding = 4;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.11f, 0.20f, 0.94f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.59f, 0.26f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.98f, 0.60f, 0.26f, 0.69f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.09f, 0.07f, 0.13f, 0.94f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.27f, 0.20f, 0.40f, 0.94f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.16f, 0.30f, 0.94f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.23f, 0.44f, 0.94f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.98f, 0.59f, 0.26f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.98f, 0.60f, 0.26f, 0.76f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.98f, 0.60f, 0.26f, 0.94f);
		colors[ImGuiCol_Button] = ImVec4(0.98f, 0.60f, 0.26f, 0.76f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.55f, 0.34f, 0.15f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.60f, 0.26f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.27f, 0.20f, 0.40f, 0.94f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.23f, 0.44f, 0.94f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.32f, 0.60f, 0.94f);
		colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.12f, 0.22f, 0.94f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.23f, 0.44f, 0.94f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.41f, 0.32f, 0.60f, 0.94f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.14f, 0.11f, 0.20f, 0.94f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.27f, 0.20f, 0.40f, 0.94f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.23f, 0.44f, 0.94f);
		colors[ImGuiCol_Tab] = ImVec4(0.66f, 0.66f, 0.87f, 0.58f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.76f, 0.76f, 1.00f, 0.88f);
		colors[ImGuiCol_TabActive] = ImVec4(0.72f, 0.72f, 0.95f, 0.81f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.65f, 0.65f, 0.87f, 0.58f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.85f, 0.51f, 0.21f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}
}

