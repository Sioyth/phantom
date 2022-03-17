#include "UI.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "scene/Entity.h"
#include "scene/SceneManager.h"

#include <iostream>

namespace Phantom
{
	Entity* UI::_nodeSelected = nullptr;

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

	void UI::DrawChildren(Entity* entity)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (entity == _nodeSelected)
			flags |= ImGuiTreeNodeFlags_Selected;
			
		bool open = ImGui::TreeNodeEx(entity->Name().c_str(), flags);
		
		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			_nodeSelected = entity;

		if(open)
		{
			for (int j = 0; j < entity->Children().size(); j++)
			{
				auto child = entity->Children()[j];
				if (child->Children().empty())
					DrawLeaf(child);
				else
					DrawChildren(child);
			}
			ImGui::TreePop();
		}
	}

	void UI::DrawLeaf(Entity* entity)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
		if (entity == _nodeSelected)
			flags |= ImGuiTreeNodeFlags_Selected;

		ImGui::TreeNodeEx(entity->Name().c_str(), flags);
			if (ImGui::IsItemClicked())
				_nodeSelected = entity;
		ImGui::TreePop();
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

		ImGui::Begin("Hierarchy");
		for (int i = 0; i < SceneManager::ActiveScene()->Entities().size(); i++)
		{
			auto entity = SceneManager::ActiveScene()->Entities()[i];
			//ignore entities with parent on first pass;
			if (entity->Parent())
				continue;

			if (entity->Children().empty())
				DrawLeaf(entity);
			else
				DrawChildren(entity);
		}
		ImGui::End();

		if(_nodeSelected)
			std::cout << _nodeSelected->Name() << std::endl;

		// temp
		static bool demo = true;
		ImGui::ShowDemoWindow(&demo);
		EndFrame();
	}
}

