#include "skip_quest.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "inputs.h"
#include "helpers.h"

namespace SkipQuest
{
	bool bSkipQuest = FALSE;
	int iStoryId = 0;

	static void OnCore(MoleMole::LevelDesignManager* _this)
	{
		UPDATE_DELAY(100);

		if (!Options.bSkipQuestAutoFinish && !bSkipQuest)
			return;

		if (iStoryId)
		{
			if (Options.bSkipQuestAutoFinish || bSkipQuest)
			{
				
				MoleMole::LevelDesignManager::FinishOWMission(_this, iStoryId, NULL);
			}
		}

		bSkipQuest = FALSE;
		iStoryId = 0;
	}

	static bool OnPacketHandler(MoleMole::NewOpenWorldModule* _this, void* pkt)
	{
		// need to try MoleMole_LevelDesignManager_GetCurrentOpenWorldAllQuest

		bool bResult = CALL_ORIGIN(OnPacketHandler, _this, pkt);

		if (_this) 
			iStoryId = _this->_currentFolowingID;

		return bResult;
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Skip Quest");

		if (ImGui::Button("Finish Quest"))
			bSkipQuest = TRUE;

		ImGui::SameLine();

		ImGui::HelpMarker("Instantly pass the quest in the open world.");

		ImGui::Checkbox("Auto Finish", &Options.bSkipQuestAutoFinish);

		ImGui::Text("Current Quest: %i", iStoryId);

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		LevelDesignEvent += OnCore;

		CreateHook(MoleMole::NewOpenWorldModule::OnPacket, OnPacketHandler);
	}
}