#include "auto_challenge.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace AutoChallenge
{
	static bool IsFinishedHandler(MoleMole::BaseLevelChallenge* _this)
	{
		return TRUE;
	}

	static bool OnEventHandler(MoleMole::BaseLevelChallenge** _this, MoleMole::BaseEvent* evt)
	{
		// MoleMole_LevelScoreManager_HandleLevelEnd

		if (Options.bAutoChallenge)
		{
			*(PVOID*)((PBYTE)((*_this)->klass) + 0x20) = IsFinishedHandler;
		}

		return CALL_ORIGIN(OnEventHandler, _this, evt);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Auto Challenge");

		ImGui::Checkbox("Enable", &Options.bAutoChallenge);

		ImGui::SameLine();

		ImGui::HelpMarker("Always 3 stars.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::BaseLevelChallenge::OnEvent, OnEventHandler);
	}
}
