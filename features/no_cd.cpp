#include "no_cd.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace NoCd
{
#pragma optimize("", off)
	static bool CanUseSkillHandler(MoleMole::MonoElfSkillButton* _this, void* skillName)
	{
		if (!Options.bNoCd)
			return CALL_ORIGIN(CanUseSkillHandler, _this, skillName);

		return TRUE;
	}

	static bool JINKHMOGDFPHandler(MoleMole::KAPEGMEPHEO* _this, void* JJJKHLEIPMH)
	{
		if (!Options.bNoCd)
			return CALL_ORIGIN(JINKHMOGDFPHandler, _this, JJJKHLEIPMH);

		return TRUE;
	}
#pragma optimize("", on)
	void Render()
	{
		ImGui::BeginGroupPanel("No CD");

		ImGui::Checkbox("Enable", &Options.bNoCd);

		ImGui::SameLine();

		ImGui::HelpMarker("Allows you to press ult without cd and without energy.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::MonoElfSkillButton::CanUseSkill, CanUseSkillHandler);
		CreateHook(MoleMole::KAPEGMEPHEO::JINKHMOGDFP, JINKHMOGDFPHandler);
	}
}