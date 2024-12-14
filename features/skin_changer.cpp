#include "skin_changer.h"

#include "globals.h"
#include "utils.h"
#include "imgui_internal.h"

#include "hooks.h"
#include "helpers.h"

namespace SkinChanger
{
	static int GetIndex(int iAvatarId)
	{
		for (int i = 0; i < _countof(Options.SkinOptions); i++)
		{
			if (Options.SkinOptions[i].iAvatarId == iAvatarId)
				return i;
		}

		return -1;
	}

	static void NewOption(int iAvatarId, int iDressId)
	{
		if (GetIndex(iAvatarId) != -1)
			return;

		for (int i = 0; i < _countof(Options.SkinOptions); i++)
		{
			if (Options.SkinOptions[i].iAvatarId != -1)
				continue;

			Options.SkinOptions[i].iAvatarId = iAvatarId;
			Options.SkinOptions[i].iDressId = iDressId;

			return;
		}
	}

	static int GetDressId(int iAvatarId)
	{
		for (INT i = 0; i < _countof(Options.SkinOptions); i++)
		{
			if (Options.SkinOptions[i].iAvatarId == iAvatarId)
				return Options.SkinOptions[i].iDressId;
		}

		return -1;
	}

	static void RequestSetDressHandler(MoleMole::NetworkManager* _this, int avatarId, int dressId)
	{
		if (!Options.bSkinChanger)
			return CALL_ORIGIN(RequestSetDressHandler, _this, avatarId, dressId);

		int iIndex = GetIndex(avatarId);

		if (iIndex != -1)
			Options.SkinOptions[iIndex].iDressId = dressId;
		else
			NewOption(avatarId, dressId);
	}

	static System::Collections::Generic::Array<MoleMole::DressDataItem*>* get_CurAvatarAllDressHandler(MoleMole::SessionUI::AvatarOperationSession* _this)
	{
		System::Collections::Generic::Array<MoleMole::DressDataItem*>* lpResult = CALL_ORIGIN(get_CurAvatarAllDressHandler, _this);

		if (lpResult)
		{
			for (SIZE_T i = 0; i < lpResult->max_length; i++)
			{
				MoleMole::DressDataItem* lpDress = lpResult->vector[i];

				if (!lpDress)
					continue;

				if (Options.bSkinChanger)
				{
					lpDress->LAACNGHLPLG = TRUE;

					if (lpDress->_FMKHHMMFOKN_k__BackingField == 4)
					{
						lpDress->NKHIDKDNEKM = lpDress->_OKIJIHDAGGA_k__BackingField; 
						lpDress->_OKIJIHDAGGA_k__BackingField = 0;
					}
				}
			}

		}

		return lpResult;
	}

	static void InitHandler(MoleMole::AvatarDataItem* _this, int avatarID, void* metaData, void* starMetaData, void* levelMetaData, int level, int star, int subStar)
	{
		CALL_ORIGIN(InitHandler, _this, avatarID, metaData, starMetaData, levelMetaData, level, star, subStar);

		if (_this)
		{
			INT iDressId = GetDressId(avatarID);

			if (iDressId != -1)
				_this->_DressID_k__BackingField = iDressId;
		}
	}

	static MoleMole::AvatarDataItem* TryGetAvatarByIDHandler(MoleMole::AvatarModule** _this, int avatarID)
	{
		MoleMole::AvatarDataItem* lpAvatarData = CALL_ORIGIN(TryGetAvatarByIDHandler, _this, avatarID);

		if (Options.bSkinChanger)
		{
			if (lpAvatarData)
			{
				INT iDressId = GetDressId(avatarID);

				if (iDressId != -1)
				{
					lpAvatarData->_DressID_k__BackingField = iDressId;
				}
			}
		}

		return lpAvatarData;
	}

	void Render()
	{
		ImGui::BeginGroupPanel("Skin Changer");

		ImGui::Checkbox("Enable", &Options.bSkinChanger);

		ImGui::SameLine();

		ImGui::HelpMarker("Unlocks all character skins.");

		ImGui::EndGroupPanel();
	}

	void Update()
	{
	}

	void Start()
	{
		CreateHook(MoleMole::NetworkManager::RequestSetDress, RequestSetDressHandler);
		CreateHook(MoleMole::SessionUI::AvatarOperationSession::get_CurAvatarAllDress, get_CurAvatarAllDressHandler);
		CreateHook(MoleMole::AvatarDataItem::Init, InitHandler);
		CreateHook(MoleMole::AvatarModule::TryGetAvatarByID, TryGetAvatarByIDHandler);
	}
}
