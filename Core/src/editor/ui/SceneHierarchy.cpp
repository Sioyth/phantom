#include "SceneHierarchy.h"
#include <imgui/imgui.h>
#include "../../scene/SceneManager.h"

namespace Phantom
{
	Entity* SceneHierarchy::_nodeSelected = nullptr;
	Entity* SceneHierarchy::_nodeDropped = nullptr;

	void SceneHierarchy::DrawChildren(Entity* entity)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (entity == _nodeSelected)
			flags |= ImGuiTreeNodeFlags_Selected;
		bool open = ImGui::TreeNodeEx(entity->Name().c_str(), flags);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			_nodeSelected = entity;

		if (open)
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

	void SceneHierarchy::Render()
	{
		ImGui::Begin("Hierarchy");
		for (int i = 0; i < SceneManager::CurrentScene()->Entities().size(); i++)
		{
			Entity* entity = SceneManager::CurrentScene()->Entities()[i].get();
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
	}

	// pass id instead
	void SceneHierarchy::DrawLeaf(Entity* entity)
	{
		;
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
}