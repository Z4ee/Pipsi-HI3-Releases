#include "instant_win.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "inputs.h"
#include "helpers.h"

namespace InstantWin
{
	static bool OnStageEndRspHandler(MoleMole::LevelEndPageContext* _this, void* rsp)
	{
		bool bResult = CALL_ORIGIN(OnStageEndRspHandler, _this, rsp);

		if (Options.bInstantWin && Options.bInstantWinNextStage && Inputs::GetState(Options.dwInstantWinKey, INPUT_TYPE_HOLD))
			MoleMole::LevelEndPageContext::OnContinueBtnClick(_this);

		return bResult;
	}

	static void OnCore(MoleMole::LevelDesignManager* _this)
	{
		if (!Options.bInstantWin || !Inputs::GetState(Options.dwInstantWinKey, INPUT_TYPE_HOLD))
			return;

		MoleMole::LevelDesignManager::LevelEndWithResult(_this, TRUE, 0, TRUE, TRUE);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Instant Win");

		ImGui::Checkbox("Enable", &Options.bInstantWin);

		ImGui::SameLine();

		ImGui::Hotkey(&Options.dwInstantWinKey);

		ImGui::SameLine();

		ImGui::HelpMarker("Passes the level instantly.");

		if (Options.bInstantWin)
		{
			ImGui::Indent();

			ImGui::Checkbox("Auto Continue", &Options.bInstantWinNextStage);

			ImGui::SameLine();

			ImGui::HelpMarker("Automatically presses the continue button. Works better without hotkey.");

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(MoleMole::LevelEndPageContext::OnStageEndRsp, OnStageEndRspHandler);

		LevelDesignEvent += OnCore;
	}
}