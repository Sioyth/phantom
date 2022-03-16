#include "UI.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "scene/Entity.h"
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

		static Entity* nodeSelected = nullptr;
		ImGui::Begin("Hierarchy");
		//Entity* entities = SceneManager::ActiveScene()->Entities();
			for (int i = 0; i < SceneManager::ActiveScene()->Entities().size(); i++)
			{
				//ignore entities with parent;
				if (SceneManager::ActiveScene()->Entities()[i].Parent())
					continue;

				// turn this into recursive function
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
				float childrenSize = SceneManager::ActiveScene()->Entities()[i].Children().size();
				if(childrenSize > 0)
					flags = ImGuiTreeNodeFlags_None;
				
				ImGui::TreeNodeEx(SceneManager::ActiveScene()->Entities()[i].Name().c_str(), flags);
				{
					for (int j = 0; j < SceneManager::ActiveScene()->Entities()[i].Children().size(); j++)
					{
						ImGui::TreeNodeEx(SceneManager::ActiveScene()->Entities()[i].Children()[j]->Name().c_str(), ImGuiTreeNodeFlags_Leaf);
						if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
							nodeSelected = SceneManager::ActiveScene()->Entities()[i].Children()[j];
					}
				}
				if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
					nodeSelected = &SceneManager::ActiveScene()->Entities()[i];
				ImGui::TreePop();
			}
			
		ImGui::End();

		// ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
		
		// temp
		static bool demo = true;
		ImGui::ShowDemoWindow(&demo);
		EndFrame();
	}
}
