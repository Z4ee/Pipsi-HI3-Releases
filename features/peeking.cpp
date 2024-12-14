#include "peeking.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "helpers.h"
#include "hooks.h"

namespace Peeking
{
	static void ApplyDitherHandler(MoleMole::MarsSimpleAvatar* _this, bool isInDither, float ditherAlpha)
	{
		if (Options.bPeeking)
			ditherAlpha = 1.f;

		return CALL_ORIGIN(ApplyDitherHandler, _this, isInDither, ditherAlpha);
	}

	static void SetStackDitherHandler(MoleMole::PJMS::PJMSBaseActor* _this, float alpha, void* stackType, bool instant)
	{
		if (Options.bPeeking)
			alpha = 1.f;

		return CALL_ORIGIN(SetStackDitherHandler, _this, alpha, stackType, instant);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Peeking");

		ImGui::Checkbox("Enable", &Options.bPeeking);

		ImGui::SameLine();

		ImGui::HelpMarker("Removes censorship under the character.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{

	}

	void Start()
	{
		CreateHook(MoleMole::MarsSimpleAvatar::ApplyDither, ApplyDitherHandler);
		CreateHook(MoleMole::PJMS::PJMSBaseActor::SetStackDither, SetStackDitherHandler);
	}
}
