#include "LM.h"
#include "SoundComponent.h"
#include "Audio/SoundNode.h"
#include "App/Scene.h"
#include "Maths/BoundingSphere.h"
#include "Graphics/Renderers/DebugRenderer.h"

#include "App/Application.h"
#include "Audio/AudioManager.h"
#include <imgui/imgui.h>
#include "Physics/LumosPhysicsEngine/PhysicsObject3D.h"

namespace Lumos
{
	SoundComponent::SoundComponent(std::shared_ptr<SoundNode>& sound)
		: m_SoundNode(sound)
	{
		m_BoundingShape = std::make_unique<maths::BoundingSphere>(sound->GetPosition(),sound->GetRadius());
	}

	void SoundComponent::OnUpdateComponent(float dt)
	{
		Physics3DComponent* physicsComponent = m_Entity->GetComponent<Physics3DComponent>();
		if (physicsComponent)
		{
			m_SoundNode->SetPosition(physicsComponent->m_PhysicsObject->GetPosition()); //TODO : Get From Entity Transform
			m_SoundNode->SetVelocity(physicsComponent->m_PhysicsObject->GetLinearVelocity());
			m_BoundingShape->SetPosition(m_SoundNode->GetPosition());
		}
	}

	void SoundComponent::DebugDraw(uint64 debugFlags)
	{
		DebugRenderer::DebugDraw(static_cast<maths::BoundingSphere*>(m_BoundingShape.get()), maths::Vector4(0.7f,0.2f,0.4f, 0.2f));
	}

	void SoundComponent::Init()
	{
		Application::Instance()->GetAudioManager()->AddSoundNode(m_SoundNode.get());
	}

	void SoundComponent::OnIMGUI()
	{
		if (ImGui::TreeNode("Sound"))
		{
			auto pos = m_SoundNode->GetPosition();
			auto radius = m_SoundNode->GetRadius();
			auto paused = m_SoundNode->GetPaused();
			auto pitch = m_SoundNode->GetPitch();
			auto referenceDistance = m_SoundNode->GetReferenceDistance();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
            ImGui::Columns(2);
            ImGui::Separator();
            
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Position");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::InputFloat3("##Position", &pos.x))
                m_SoundNode->SetPosition(pos);
            
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Radius");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::InputFloat("##Radius", &radius))
                m_SoundNode->SetRadius(radius);
            
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Pitch");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::InputFloat("##Pitch", &pitch))
                m_SoundNode->SetPitch(pitch);
            
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Reference Distance");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::DragFloat("##Reference Distance", &referenceDistance))
                m_SoundNode->SetReferenceDistance(referenceDistance);
            
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Paused");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::Checkbox("##Paused", &paused))
                m_SoundNode->SetPaused(paused);
            
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::PopStyleVar();
            
			ImGui::TreePop();
		}
	}
}
