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
	Entity* UI::_nodeDropped = nullptr;
	glm::vec2 UI::currentViewPortSize;

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
				Entity* child = entity->Children()[j];
				if (child->Children().empty())
					DrawLeaf(entity->Children()[j]);
				else
					DrawChildren(child->Children()[j]);
			}
			ImGui::TreePop();
		}
	}
	// pass id instead
	void UI::DrawLeaf(Entity* entity)
	{;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth;
		if (entity == _nodeSelected)
			flags |= ImGuiTreeNodeFlags_Selected;

		ImGui::TreeNodeEx(entity->Name().c_str(), flags);
			if (ImGui::IsItemClicked())
				_nodeSelected = entity;

			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("moving", nullptr, 0);
				_nodeDropped = entity;
				ImGui::Text(entity->Name().c_str());
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				// Temp, does this by passing Refereces of the Entity UID change parent and children to be UID references
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("moving"))
				{
					if (_nodeDropped->Parent())
						_nodeDropped->Parent()->RemoveChild(_nodeDropped);
					entity->AddChild(_nodeDropped);
					_nodeDropped->SetParent(entity);
				}
				ImGui::EndDragDropTarget();
			}

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
			Entity* entity = SceneManager::ActiveScene()->Entities()[i].get();
			//ignore entities with parent on first pass;
			if (entity->Parent())
				continue;

			if (entity->Children().empty())
			{
				DrawLeaf(entity);
				//ImGui::Separator();
				////
				//if (ImGui::BeginDragDropTarget())
				//{
				//	ImGui::AcceptDragDropPayload("_TREENODE");
				//	ImGui::EndDragDropTarget();
				//}
			}
			else
				DrawChildren(entity);
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene ViewPort");
		ImVec2 imvpSize = ImGui::GetContentRegionAvail();
			glm::vec2 newViewPortSize = { imvpSize.x, imvpSize.y };

			ImGui::Image((void*)Renderer::Instance().ColorFrameBuffer().Texture(), imvpSize, ImVec2(0, 1), ImVec2(1, 0));
			//if (newViewPortSize != currentViewPortSize)
			//{
			//	currentViewPortSize = newViewPortSize;
			//	//Renderer::Instance().ColorFrameBuffer().Resize(currentViewPortSize.x, currentViewPortSize.y);
			//	std::cout << "Resize" << std::endl;
			//}
		ImGui::End();
		ImGui::PopStyleVar();

		/*static bool demo = true;
		ImGui::ShowDemoWindow(&demo);*/
		EndFrame();
	}
}

