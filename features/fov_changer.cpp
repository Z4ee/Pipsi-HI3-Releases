#include "fov_changer.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace FovChanger
{
	static void set_fieldOfViewHandler(void* _this, float value)
	{
		FLOAT flValue;

		if (Options.bFovChanger)
			flValue = Options.flFovChangerValue;
		else
			flValue = value;

		return CALL_ORIGIN(set_fieldOfViewHandler, _this, flValue);
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Fov Changer");

		ImGui::Checkbox("Enable", &Options.bFovChanger);

		if (Options.bFovChanger)
		{
			ImGui::Indent();

			ImGui::SliderFloat("Value", &Options.flFovChangerValue, 1.f, 360.f, "%.1f");

			ImGui::Unindent();
		}

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(UnityEngine::Camera::set_fieldOfView, set_fieldOfViewHandler);
	}
}