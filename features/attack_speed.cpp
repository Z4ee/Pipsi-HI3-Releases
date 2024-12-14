#include "attack_speed.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace AttackSpeed
{
	static float GetFixedAttackSpeedRatioHandler(MoleMole::BaseMonoAvatar* _this)
	{
		if (!Options.bAttackSpeed)
			return CALL_ORIGIN(GetFixedAttackSpeedRatioHandler, _this);

		return Options.flAttackSpeedValue;
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Attack Speed");

		ImGui::Checkbox("Enable", &Options.bAttackSpeed);

		ImGui::SameLine();

		ImGui::HelpMarker("Avatar attack speed changer.");

		if (Options.bAttackSpeed)
		{
			ImGui::Indent();

			ImGui::SliderFloat("Value", &Options.flAttackSpeedValue, 0.f, 100.f, "%.1f");

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(MoleMole::BaseMonoAvatar::GetFixedAttackSpeedRatio, GetFixedAttackSpeedRatioHandler);
	}
}