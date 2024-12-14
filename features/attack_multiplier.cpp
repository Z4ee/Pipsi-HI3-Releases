#include "attack_multiplier.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace AttackMultiplier
{
	static bool MBBCKMHHDJBHandler(void* _this, void* OIPIHEPMNNP)
	{
		if (Options.bAttackMultiplier)
		{
			for (int i = 0; i < Options.iAttackMultiplierValue - 1; i++)
				CALL_ORIGIN(MBBCKMHHDJBHandler, _this, OIPIHEPMNNP);
		}

		return CALL_ORIGIN(MBBCKMHHDJBHandler, _this, OIPIHEPMNNP);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Attack Multiplier");

		ImGui::Checkbox("Enable", &Options.bAttackMultiplier);

		ImGui::SameLine();

		ImGui::HelpMarker("Allows you to increase the number of attacks.");

		if (Options.bAttackMultiplier)
		{
			ImGui::Indent();

			ImGui::SliderInt("Value", &Options.iAttackMultiplierValue, 1, 100);

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::FGDGIKAJJMB::MBBCKMHHDJB, MBBCKMHHDJBHandler);
	}
}