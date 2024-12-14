#include "instant_win.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "inputs.h"
#include "helpers.h"

namespace KillAura
{
	static void OnCore(MoleMole::LevelDesignManager* _this)
	{
		if (!Options.bKillAura || !Inputs::GetState(Options.dwKillAuraKey, INPUT_TYPE_HOLD))
			return;

		if (Options.bKillAuraNoAnimation)
			MoleMole::LevelDesignManager::ClearAllMonsters(_this, TRUE, TRUE);
		else
			MoleMole::LevelDesignManager::KillAllMonsters(_this, TRUE, TRUE);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Kill Aura");

		ImGui::Checkbox("Enable", &Options.bKillAura);

		ImGui::SameLine();

		ImGui::Hotkey(&Options.dwKillAuraKey);

		ImGui::SameLine();

		ImGui::HelpMarker("Kills all monsters nearby.");

		if (Options.bKillAura)
		{
			ImGui::Indent();

			ImGui::Checkbox("No Animation", &Options.bKillAuraNoAnimation);

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		LevelDesignEvent += OnCore;
	}
}