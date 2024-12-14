#include "avatar_speed.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "helpers.h"

namespace AvatarSpeed
{
	void Render()
	{
		ImGui::BeginGroupPanel("Move Speed");

		ImGui::Checkbox("Enable", &Options.bAvatarSpeed);

		ImGui::SameLine();

		ImGui::HelpMarker("Avatar move speed changer.");

		if (Options.bAvatarSpeed)
		{
			ImGui::Indent();

			ImGui::SliderFloat("Value", &Options.flAvatarSpeedValue, 0.f, 10.f, "%.1f");

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
		UPDATE_DELAY(100);

		MoleMole::BaseMonoAvatar* lpLocalAvatar = Helpers::GetLocalAvatar();

		if (!lpLocalAvatar)
			return;

		if (Options.bAvatarSpeed)
			lpLocalAvatar->_moveSpeedRatio = Options.flAvatarSpeedValue;
		else
			lpLocalAvatar->_moveSpeedRatio = 1.f;
	}

	void Start()
	{

	}
}