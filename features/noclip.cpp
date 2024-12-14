#include "noclip.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "inputs.h"
#include "helpers.h"

namespace Noclip
{
	bool bIsApplied = FALSE;

	static void OnVelocity(UnityEngine::Rigidbody* lpRigidbody, Vector3* value)
	{
		MoleMole::BaseMonoAvatar* lpLocalAvatar = Helpers::GetLocalAvatar();

		if (!lpLocalAvatar)
			return;

		UnityEngine::Transform* lpTransform = Helpers::GetTransform(lpLocalAvatar);

		if (!lpTransform)
			return;

		Vector3 Direction = {};

		if (Inputs::GetState('W', INPUT_TYPE_HOLD)
			|| Inputs::GetState('A', INPUT_TYPE_HOLD)
			|| Inputs::GetState('S', INPUT_TYPE_HOLD)
			|| Inputs::GetState('D', INPUT_TYPE_HOLD))
		{
			Helpers::GetForward(lpTransform, &Direction);
		}

		if (Inputs::GetState(VK_SPACE, INPUT_TYPE_HOLD))
			Helpers::GetUp(lpTransform, &Direction);

		if (Inputs::GetState(VK_SHIFT, INPUT_TYPE_HOLD))
			Helpers::GetDown(lpTransform, &Direction);

		Vector3 Velocity = Direction * Options.flNoclipSpeed;

		value->x = Velocity.x;
		value->y = Velocity.y;
		value->z = Velocity.z;
	}

	static void INTERNAL_set_velocityHandler(UnityEngine::Rigidbody* _this, Vector3* value)
	{
		if (_this && Options.bNoclip && Inputs::GetState(Options.dwNoclipKey, INPUT_TYPE_TOGGLE) && _this == Helpers::GetRigidbody())
			Noclip::OnVelocity(_this, value);

		return CALL_ORIGIN(INTERNAL_set_velocityHandler, _this, value);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Noclip");

		ImGui::Checkbox("Enable", &Options.bNoclip);

		ImGui::SameLine();

		ImGui::Hotkey(&Options.dwNoclipKey);

		ImGui::SameLine();

		ImGui::HelpMarker("Allows you to fly and go through walls.");

		if (Options.bNoclip)
		{
			ImGui::Indent();

			ImGui::SliderFloat("Speed", &Options.flNoclipSpeed, 0.01f, 100.f, "%.2f");

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
		UnityEngine::Rigidbody* lpRigidbody = Helpers::GetRigidbody();

		if (!lpRigidbody)
			return;

		UPDATE_DELAY(20);

		if (!Options.bNoclip || !Inputs::GetState(Options.dwNoclipKey, INPUT_TYPE_TOGGLE))
		{
			if (!bIsApplied)
				return;

			UnityEngine::Rigidbody::set_detectCollisions(lpRigidbody, TRUE);

			bIsApplied = FALSE;
		}
		else
		{
			UnityEngine::Rigidbody::set_collisionDetectionMode(lpRigidbody, UnityEngine::CollisionDetectionMode_Continuous);
			UnityEngine::Rigidbody::set_detectCollisions(lpRigidbody, FALSE);

			bIsApplied = TRUE;
		}
	}

	void Start()
	{
		CreateHook(UnityEngine::Rigidbody::INTERNAL_set_velocity, Noclip::INTERNAL_set_velocityHandler);
	}
}