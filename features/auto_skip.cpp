#include "auto_skip.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace AutoSkip
{
	namespace Dialog
	{
		static void RefreshCheckStatusHandler(MoleMole::ScenarioSkipConfirmDialogContext* _this)
		{
			CALL_ORIGIN(RefreshCheckStatusHandler, _this);

			if (Options.bAutoSkip && Options.bAutoSkipDialog)
				MoleMole::ScenarioSkipConfirmDialogContext::OnClickOKBtn(_this);
		}

		static void SwitchAvatarVisibleHandler(MoleMole::EventDialogContext* _this, bool visible)
		{
			CALL_ORIGIN(SwitchAvatarVisibleHandler, _this, visible);

			if (Options.bAutoSkip && Options.bAutoSkipDialog)
			{
				MoleMole::MonoEventCanvas* lpEventCanvas = MoleMole::EventDialogContext::get_EventCanvas(_this);

				if (lpEventCanvas)
					MoleMole::MonoEventCanvas::OnSkipBtnClick(lpEventCanvas);
			}
		}
	}

	namespace PlotPage
	{
		static void OnBGClickHandler(MoleMole::InLevelPlotPageContext* _this, void* evtData)
		{
			CALL_ORIGIN(OnBGClickHandler, _this, evtData);

			if (Options.bAutoSkip && Options.bAutoSkipPlotPage)
			{
				MoleMole::InLevelPlotPageContext::SkipPlot(_this);
			}
		}
	}

	namespace PlotTrackLine
	{
		static void UpdateHandler(MoleMole::PlotTrackLine::PlotLine* _this, void* deltaTime)
		{
			CALL_ORIGIN(UpdateHandler, _this, deltaTime);

			if (Options.bAutoSkip && Options.bAutoSkipPlotTrackLine && _this)
				MoleMole::PlotTrackLine::PlotUtil::TrySkip(_this);
		}
	}

	namespace ResultDialog
	{
		static bool OnPacketHandler(MoleMole::LevelResultDialogContext* _this, void* pkt)
		{
			BOOL bResult = CALL_ORIGIN(OnPacketHandler, _this, pkt);

			if (Options.bAutoSkip && Options.bAutoSkipResultDialog && _this)
				MoleMole::LevelResultDialogContext::OnOKBtnClick(_this);
			
			return bResult;
		}

		static bool OnPlayerLevelUpNotifyHandler(MoleMole::LevelResultDialogContext* _this, void* ntf)
		{
			BOOL bResult = CALL_ORIGIN(OnPlayerLevelUpNotifyHandler, _this, ntf);

			if (Options.bAutoSkip && Options.bAutoSkipResultDialog && _this)
				MoleMole::LevelResultDialogContext::OnOKBtnClick(_this);
			
			return bResult;
		}
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Auto Skip");

		ImGui::Checkbox("Enable", &Options.bAutoSkip);
		
		if (Options.bAutoSkip)
		{
			ImGui::Indent();

			if (ImGui::BeginCombo("Events", "Select Events..."))
			{
				ImGui::Checkbox("Dialog", &Options.bAutoSkipDialog);
				ImGui::Checkbox("Plot Page", &Options.bAutoSkipPlotPage);
				ImGui::Checkbox("Plot Track Line", &Options.bAutoSkipPlotTrackLine);
				ImGui::Checkbox("Result Dialog", &Options.bAutoSkipResultDialog);

				ImGui::EndCombo();
			}

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(MoleMole::ScenarioSkipConfirmDialogContext::RefreshCheckStatus, Dialog::RefreshCheckStatusHandler);
		CreateHook(MoleMole::EventDialogContext::SwitchAvatarVisible, Dialog::SwitchAvatarVisibleHandler);
		CreateHook(MoleMole::InLevelPlotPageContext::OnBGClick, PlotPage::OnBGClickHandler);
		CreateHook(MoleMole::PlotTrackLine::PlotLine::Update, PlotTrackLine::UpdateHandler);
		CreateHook(MoleMole::LevelResultDialogContext::OnPlayerLevelUpNotify, ResultDialog::OnPlayerLevelUpNotifyHandler);
	}
}