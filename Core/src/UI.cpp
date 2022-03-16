#include "UI.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "scene/SceneManager.h"

namespace Phantom
{
	bool UI::Init(GLFWwindow* window)
	{

		// TEMP -  put this in UI class.
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) 
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

	void UI::Render()
	{
	
		NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		
		/*ImGui::Begin("Hierarchy");
		for (int i = 0; i < entities; i++)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
			ImGui::TreeNodeEx("Object B");
			ImGui::TreePop();
			ImGui::End();

			ImGui::Begin("Components");
		}*/

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

		ImGui::Begin("Hierarchy");
		ImGui::TreeNodeEx("Object A");
		ImGui::TreeNodeEx("Object B");
		ImGui::TreeNodeEx("Object C");
		ImGui::End();
		
		// temp
		static bool demo = true;
		ImGui::ShowDemoWindow(&demo);
		EndFrame();
	}
}
