#include "SongSelectionUIController.hpp"

#include "utils.h"
#include "il2cpp_utils.hpp"
#include "LevelDatabase.hpp"
#include "logger.h"
#include "List.hpp"
#include "GameObject.hpp"
#include "LevelData.hpp"

using namespace CSharp;


namespace SongSelectionUIController {

	void AddPageIndicator(Il2CppObject* self)
	{
		static auto parentPropertyGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "parent");
		static auto parentPropertySet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "parent");

		static auto parentTransformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");
		static auto parentTransformSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");


		static auto gameObjectGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "gameObject");
		static auto transformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "transform");


		static auto positionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "position");
		static auto positionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "position");

		static auto anchoredPositionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition");
		static auto anchoredPositionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition");

		static auto anchoredPosition3DGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition3D");
		static auto anchoredPosition3DSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition3D");

		static auto offsetMinGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMin");
		static auto offsetMinSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMin");

		static auto offsetMaxGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMax");
		static auto offsetMaxSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMax");

		static auto anchorMinSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchorMin");
		static auto anchorMaxSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchorMax");
		static auto pivotSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "pivot");
		static auto sizeDeltaSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "sizeDelta");


		// Create new page indicator

		List<Il2CppObject*> pageCentersList(il2cpp_utils::GetFieldValue(self, "pageCentersList"));
		Il2CppObject* centerListParent;
		il2cpp_utils::RunMethod(&centerListParent, pageCentersList[0], parentPropertyGet);

		Il2CppObject* centerObject = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
		Il2CppObject* center = GameObject::AddComponent(centerObject, "UnityEngine", "RectTransform");
		il2cpp_utils::RunMethod(center, parentPropertySet, centerListParent);

		Vector3 pos1, pos2;
		il2cpp_utils::RunMethod(&pos1, pageCentersList[1], anchoredPosition3DGet);
		il2cpp_utils::RunMethod(&pos2, pageCentersList[2], anchoredPosition3DGet);
		float updates = pos2.x - pos1.x;
		LOG("Page update space %f\n", updates);

		Vector2 anchoredPosition4, offsetMin4, offsetMax4;
		Vector3 anchoredPosition3D4;
		il2cpp_utils::RunMethod(&anchoredPosition4, pageCentersList[4], anchoredPositionGet);
		il2cpp_utils::RunMethod(&anchoredPosition3D4, pageCentersList[4], anchoredPosition3DGet);
		il2cpp_utils::RunMethod(&offsetMin4, pageCentersList[4], offsetMinGet);
		il2cpp_utils::RunMethod(&offsetMax4, pageCentersList[4], offsetMaxGet);

		LOG("anchoredPosition4 (%f, %f)\n", anchoredPosition4.x, anchoredPosition4.y);
		LOG("offsetMin4 (%f, %f)\n", offsetMin4.x, offsetMin4.y);
		LOG("offsetMax4 (%f, %f)\n", offsetMax4.x, offsetMax4.y);
		LOG("anchoredPosition3D4 (%f, %f, %f)\n", anchoredPosition3D4.x, anchoredPosition3D4.y, anchoredPosition3D4.z);


		Vector2 anchoredPosition{ anchoredPosition4.x + updates, 0 };//anchoredPosition4.x + updates
		Vector3 anchoredPosition3D{ anchoredPosition4.x + updates, 0, 0 };
		Vector2 anchorMin{ 0,0 },
			anchorMax{ 0,0 },
			offsetMin{ offsetMin4.x + updates , 0 },
			offsetMax{ offsetMax4.x + updates, 0 },
			pivot{ 0.5, 0.5 },
			sizeDelta{ -0.16, 0 };


		il2cpp_utils::RunMethod(center, anchoredPositionSet, &anchoredPosition);
		il2cpp_utils::RunMethod(center, anchoredPosition3DSet, &anchoredPosition3D);
		il2cpp_utils::RunMethod(center, anchorMinSet, &anchorMin);
		il2cpp_utils::RunMethod(center, anchorMaxSet, &anchorMax);
		il2cpp_utils::RunMethod(center, offsetMinSet, &offsetMin);
		il2cpp_utils::RunMethod(center, offsetMaxSet, &offsetMax);
		il2cpp_utils::RunMethod(center, pivotSet, &pivot);
		il2cpp_utils::RunMethod(center, sizeDeltaSet, &sizeDelta);

		pageCentersList.Add(center);


		Il2CppObject* songSelPaginatedIndicator = il2cpp_utils::GetFieldValue(self, "songSelPaginatedIndicator");
		List<Il2CppObject*> pageMarkers(il2cpp_utils::GetFieldValue(songSelPaginatedIndicator, "pageMarkers"));
		Il2CppObject* toInstantiate;
		il2cpp_utils::RunMethod(&toInstantiate, pageMarkers[0], gameObjectGet);
		Il2CppObject* centerTarget = GameObject::Instantiate(toInstantiate);
		Il2CppObject* rectTransform = GameObject::GetComponent(centerTarget, "UnityEngine", "RectTransform");
		
		Il2CppObject* parentToSet;
		Il2CppObject* parentRectTransform = GameObject::GetComponent(toInstantiate, "UnityEngine", "RectTransform");;
		il2cpp_utils::RunMethod(&parentToSet, parentRectTransform, parentPropertyGet);
		il2cpp_utils::RunMethod(rectTransform, parentPropertySet, parentToSet);

		Vector3 newPosition{ 0, 1.234978f, 4.965f }; //TODO calculate page indicator position dynamically
		il2cpp_utils::RunMethod(rectTransform, positionSet, &newPosition);

		pageMarkers.Add(rectTransform);
	}


	void AddTestSong(Il2CppObject* self)
	{
		static auto gameObjectGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "gameObject");
		
		static auto parentTransformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");
		static auto parentTransformSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");

		static auto positionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "position");
		static auto positionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "position");


		Il2CppObject* panelToCopy;
		List<Il2CppObject*> songPanelUIControllerList(il2cpp_utils::GetFieldValue(self, "songPanelUIControllerList"));
		il2cpp_utils::RunMethod(&panelToCopy, songPanelUIControllerList[16], gameObjectGet);
		Il2CppObject* panelGO = GameObject::Instantiate(panelToCopy);
		Il2CppObject* panel = GameObject::GetComponent(panelGO, "", "SongPanelUIController");

		Il2CppObject* panelToCopyTransform = GameObject::GetComponent(panelToCopy, "UnityEngine", "Transform");
		Il2CppObject* panelTransform = GameObject::GetComponent(panelGO, "UnityEngine", "Transform");

		Il2CppObject* parentToSet;
		il2cpp_utils::RunMethod(&parentToSet, panelToCopyTransform, parentTransformGet);
		il2cpp_utils::RunMethod(panelTransform, parentTransformSet, parentToSet);

		int i = 2;
		Vector3 position{ 8.88903f + (1.24001f * (i + 5)), 1.117992f, 5.039f };
		il2cpp_utils::RunMethod(panelTransform, positionSet, &position);

		int32_t panelChildCount;
		il2cpp_utils::GetFieldValue(&panelChildCount, self, "panelChildCount");
		panelChildCount++;
		il2cpp_utils::SetFieldValue(self, "panelChildCount", &panelChildCount);

		int32_t levelIndex = 22;
		il2cpp_utils::SetFieldValue(panel, "levelDataIndex", &levelIndex);

		//TODO: Create container class for Dictionary
		Il2CppObject* nameToPage;
		il2cpp_utils::GetFieldValue(&nameToPage, self, "nameToPage");
		int32_t page = 6;
		il2cpp_utils::RunMethod(nameToPage, "Add", il2cpp_utils::createcsstr("test"), &page);
	}


	MAKE_HOOK(Start, Il2CppObject*, Il2CppObject* self)
	{


		Il2CppObject* ret = Start_orig(self);
		AddPageIndicator(self);
		AddTestSong(self);
		return ret;
	}



	
	
	MAKE_HOOK(OnClickSong, void, Il2CppObject* self)
	{
		int32_t levelDataIndex;
		il2cpp_utils::GetFieldValue(&levelDataIndex, self, "levelDataIndex");
		if (levelDataIndex > 18) //Get value from levelDatabase
		{
			//Custom map!
			//Create LevelData object corresponding to the 
			//Replace song in folder (is done when creating the level data object for now)
			//Call static SetLevel on GameManager to update with static level information.
			LOG("You clicked on a custom song!\n");
			std::ifstream i("Custom Levels/x02/level.json");
			json j;
			i >> j;

			LevelData data;
			Il2CppObject* levelData = data.Load(j["levelData"]);

			//Our song should be loaded by now
			
			//UpdateSelectedSong(il2cpp_utils::GetFieldValue(self, "parent"), self);
			
			//Move to start and store as variable
			//auto UpdateSelectedSong = il2cpp_utils::FindMethod(
			//	il2cpp_utils::GetClassFromName("", "SongSelectionUIController"),
			//	"UpdateSelectedSong",
			//	{ il2cpp_utils::GetClassFromName("", "SongPanelUIController") }
			//);
			//
			////TODO FIX ME, throws exception
			//il2cpp_utils::RunMethod(il2cpp_utils::GetFieldValue(self, "parent"), UpdateSelectedSong, self);
			auto songController = il2cpp_utils::GetFieldValue(self, "parent");
			bool active = true, inactive = false;

			auto lastSongPanelSelected = il2cpp_utils::GetFieldValue(songController, "lastSongPanelSelected");
			if (lastSongPanelSelected != nullptr)
			{
				il2cpp_utils::RunMethod(lastSongPanelSelected, "SetSelectionOutlineState", &inactive);
			}

			auto lrgAlbumArt = il2cpp_utils::GetFieldValue(songController, "lrgAlbumArt");
			auto sprite = il2cpp_utils::GetFieldValue(il2cpp_utils::GetFieldValue(self, "songImage"), "m_Sprite");
			il2cpp_utils::RunMethod(lrgAlbumArt, "set_sprite", sprite);

			auto startBtn = il2cpp_utils::GetFieldValue(songController, "startSongUIButton");
			il2cpp_utils::RunMethod(startBtn, "SetActive", &active);

			//TODO Add leveldata to AlbumArtDatabase
			//il2cpp_utils::RunMethod(songController, "UpdateSongInfoPanel", self);

			auto songInfoCanvas = il2cpp_utils::GetFieldValue(songController, "songInfoCanvas");
			il2cpp_utils::RunMethod(songInfoCanvas, "set_enabled", &active);
			
			auto rightTrainingPosterPanel = il2cpp_utils::GetFieldValue(songController, "rightTrainingPosterPanel");
			il2cpp_utils::RunMethod(rightTrainingPosterPanel, "set_enabled", &active);

			//TODO elements to disable

			il2cpp_utils::RunMethod(songController, "SelectedEasyDifficulty");

			auto selectionOutline = il2cpp_utils::GetFieldValue(self, "selectionOutline");
			if (selectionOutline != nullptr)
			{
				Il2CppObject* go;
				il2cpp_utils::RunMethod(&go, selectionOutline, "get_gameObject");
				il2cpp_utils::RunMethod(go, "SetActive", &active);
			}




			//il2cpp_utils::RunMethod(self, "SetSong");


			Il2CppObject* gameManager;
			if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
				LOG("WARNING: Failed to get instance of GameManager\n");

			int32_t difficulty = 0;

			Il2CppObject* levels = il2cpp_utils::GetFieldValue(gameManager, "levels");
			List<Il2CppObject*> levelDataDB(il2cpp_utils::GetFieldValue(levels, "levelData"));
			Il2CppObject* songSwitch = il2cpp_utils::GetFieldValue(levelDataDB[15], "songSwitch");
			il2cpp_utils::SetFieldValue(levelData, "songSwitch", songSwitch);
			Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(levelData, "maps"));
			Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, static_cast<int32_t>(0)); //GameMap

			il2cpp_utils::RunMethod(songSwitch, "SetValue");
			
			il2cpp_utils::RunMethod(gameManager, "SetLevelInternal", map);

			Il2CppObject* gameEvent = il2cpp_utils::GetFieldValue(self, "songSelectedEvent");
			il2cpp_utils::RunMethod(gameEvent, "Raise");
			

		}
		else
			OnClickSong_orig(self); // We are not clicking on an custom level, just call stuff in ordinary fashion
	}

	MAKE_HOOK(Get_SourceClipName, Il2CppString*, Il2CppObject* self)
	{
		Il2CppString* str = Get_SourceClipName_orig(self);

		Il2CppObject* gameManager;
		if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
			LOG("WARNING: Failed to get instance of GameManager\n");
		bool playing = false;
		il2cpp_utils::GetFieldValue(&playing, gameManager, "playing");
		if (playing)
		{
			Il2CppString* str2, *str3;
			il2cpp_utils::GetFieldValue(&str2, il2cpp_utils::GetClassFromName("", "MusicManager"), "songName");
			Il2CppObject* player;
			il2cpp_utils::GetFieldValue(&player, il2cpp_utils::GetClassFromName("", "MusicManager"), "player");

			il2cpp_utils::RunMethod(&str3, player, "GetCurrentClipName");
			if (str != nullptr && str2 != nullptr && str3 != nullptr)
				LOG("\tGet_SourceClipName = %s\nMusicManager.songName = %s\nPlayer.GetCurrentClipName = %s\n\n",
					to_utf8(csstrtostr(str)).c_str(),
					to_utf8(csstrtostr(str2)).c_str(),
					to_utf8(csstrtostr(str3)).c_str()
				);
		}


		return str;
	}


	void initHooks(funchook_t* funchookp)
	{
		Start_orig = (Start_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "Start", 0)->methodPointer;
		INSTALL_HOOK(Start);

		OnClickSong_orig = (OnClickSong_t)il2cpp_utils::GetMethod("", "SongPanelUIController", "OnClick", 0)->methodPointer;
		INSTALL_HOOK(OnClickSong);

		//Get_SourceClipName_orig = (Get_SourceClipName_t)il2cpp_utils::GetMethod("SonicBloom.Koreo", "Koreography", "get_SourceClipName", 0)->methodPointer;
		//INSTALL_HOOK(Get_SourceClipName);
	}

};

