#include "dump_enemies.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace DumpEnemies
{
	static MoleMole::BaseMonoEntity* get_AttackTargetHandler(MoleMole::BaseMonoMonster* _this)
	{
		if (Options.bDumpEnemies)
			return NULL;

		return CALL_ORIGIN(get_AttackTargetHandler, _this);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Dumb Enemies");

		ImGui::Checkbox("Enable", &Options.bDumpEnemies);

		ImGui::SameLine();

		ImGui::HelpMarker("Prevents monsters from moving/attacking.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(MoleMole::BaseMonoMonster::get_AttackTarget, get_AttackTargetHandler);
	}
}