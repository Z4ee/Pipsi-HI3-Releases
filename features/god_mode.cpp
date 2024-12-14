#include "god_mode.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace GodMode
{
#pragma optimize("", off)
	static bool IHPBALDABDKHandler(MoleMole::KAPEGMEPHEO* _this, void* OIPIHEPMNNP)
	{
		if (!Options.bGodMode)
			return CALL_ORIGIN(IHPBALDABDKHandler, _this, OIPIHEPMNNP);

		return FALSE;
	}

	static bool MBBCKMHHDJBHandler(MoleMole::KAPEGMEPHEO* _this, void* OIPIHEPMNNP)
	{
		if (!Options.bGodMode)
			return CALL_ORIGIN(MBBCKMHHDJBHandler, _this, OIPIHEPMNNP);

		return FALSE;
	}
#pragma optimize("", on)

	void Render()
	{
		ImGui::BeginGroupPanel("God Mode");

		ImGui::Checkbox("Enable", &Options.bGodMode);

		ImGui::SameLine();

		ImGui::HelpMarker("Invincibility.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::KAPEGMEPHEO::MBBCKMHHDJB, MBBCKMHHDJBHandler);
		CreateHook(MoleMole::KAPEGMEPHEO::IHPBALDABDK, IHPBALDABDKHandler);
	}
}
