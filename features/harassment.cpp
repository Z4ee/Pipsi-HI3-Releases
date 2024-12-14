#include "harassment.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "helpers.h"
#include "hooks.h"

namespace Harassment
{
	static bool get_EnableGalTouchActionHandler()
	{
		if (!Options.bHarassment)
			return CALL_ORIGIN(get_EnableGalTouchActionHandler);

		return TRUE;
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Harassment");

		ImGui::Checkbox("Enable", &Options.bHarassment);

		ImGui::SameLine();

		ImGui::HelpMarker("Allows you to click on a character body in the main menu.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::ExcelMeta::ConstValueDataReaderExtend::get_EnableGalTouchAction, get_EnableGalTouchActionHandler);
	}
}