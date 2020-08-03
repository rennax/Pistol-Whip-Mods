#include "GameManager.hpp"
#include "il2cpp_utils.hpp"
#include "utils.h"
#include "logger.h"
#include "LevelManager.hpp"
#include "GeoSet.hpp"
#include "LevelData.hpp"
#include "AssetBundle.hpp"
#include "List.hpp"
#include "TrackData.hpp"
#include "Messenger.hpp"

#include "WwiseKoreographySet.hpp"
#include "TempoSectionDef.hpp"
#include "Koreography.hpp"
#include "TrackSection.hpp"
#include "SceneAppearanceManager.hpp"

namespace GameManager {



	LevelData* data = nullptr;
	Il2CppObject* levelData = nullptr;

	static bool pf1 = false, pf2;

	MAKE_HOOK(OnSceneSelect, void, void* self) {
		LOG("Called GameManager.OnSceneSelect() hook\n");
		OnSceneSelect_orig(self);
	}

	MAKE_HOOK(Start, void, void* self) {
		LOG("Called GameManager.Start() hook\n");

		Start_orig(self);
	}

	Il2CppObject* msg = nullptr;

	MAKE_HOOK(Update, void, void* self) {
		SHORT keyState;
		

		if ((keyState = GetAsyncKeyState(VK_F1)) && pf1 == false)// & 0x8000
		{//Tries to start level
			LOG("Pressed F1\n");
			pf1 = true;
			SceneAppearanceManager::overwriteOnLevelSelect = true;

			AssetBundle::Init();

			std::ifstream i("Custom Levels/x02/level.json");
			json j;
			i >> j;
			//std::string s = j.dump();
			//LOG("%s\n", s.c_str());

			data = new LevelData();
			std::string version = j["version"];
			LOG("%s\n", version.c_str());
			levelData = data->Load(j["levelData"]);

			
			Il2CppObject* levels = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			Il2CppObject* lastReleasedScene = il2cpp_utils::GetFieldValue(levels, "lastReleasedScene");
			il2cpp_utils::SetFieldValue(levelData, "songSwitch", il2cpp_utils::GetFieldValue(lastReleasedScene, "songSwitch"));
			Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(levelData, "maps"));
			Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, 0); //GameMap

			//il2cpp_utils::SetFieldValue(levelData, "sections", il2cpp_utils::GetFieldValue(lastReleasedScene, "sections"));


			if (!il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "SetLevelInternal", map))
				LOG("WARNING: Failed call to GameManager.SetLevelInternal(GameMap)\n");

			il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "OnStartButton");


		}
		else if (GetAsyncKeyState(VK_F2) && pf2 == false) 
		{//
			pf2 = true;

			Il2CppObject* levels = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			Il2CppObject* lastReleasedScene = il2cpp_utils::GetFieldValue(levels, "lastReleasedScene");
			Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(lastReleasedScene, "maps"));
			Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, (int)Difficulty::Easy); //GameMap
			Il2CppObject* trackData = il2cpp_utils::GetFieldValue(map, "trackData");
			Il2CppObject* koreo = il2cpp_utils::GetFieldValue(trackData, "koreography");
			
			Koreography koreography(koreo);
			json j = koreography.Dump();
			std::ofstream o = std::ofstream("Koreography.json");
			o << std::setw(4) << j << std::endl;
			o.close();

			Il2CppObject* lvlDb = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			//Il2CppArray* koreoSets = nullptr;
			//il2cpp_utils::GetFieldValue(koreoSets, lvlDb, "koreoSets");


			Il2CppObject* frontLotKoreoSet = il2cpp_utils::GetFieldValue(levels, "frontLotKoreoSet");
			WwiseKoreographySet koreoSet(koreo, frontLotKoreoSet);
			
			j.clear();
			j = koreoSet.Dump();
			o = std::ofstream("WWiseKoreoSetDump.json");
			o << std::setw(4) << j << std::endl;
			o.close();

			LevelData level(lastReleasedScene);
			j.clear();
			j = level.Dump();
			o = std::ofstream("LevelData.json");
			o << std::setw(4) << j << std::endl;
			o.close();

			j.clear();
			List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(lastReleasedScene, "sections"));
			LOG("number of sections %d\n", sections.Count());
			TrackSection section(sections[0]);
			j = section.Dump();
			o = std::ofstream("TrackSection.json");
			o << std::setw(4) << j << std::endl;
			o.close();


		}
		if (GetAsyncKeyState(VK_F3))
		{
			pf1 = false;
			pf2 = false;
		}

		Update_orig(self);
	}

	void initHooks(funchook_t* funchookp)
	{
		LOG("GameManager::initHooks()\n");
		 
		OnSceneSelect_orig = (OnSceneSelect_t)il2cpp_utils::GetMethod("", "GameManager", "OnSceneSelect", 0)->methodPointer;
		INSTALL_HOOK(OnSceneSelect);
		
		Update_orig = (Update_t)il2cpp_utils::GetMethod("", "GameManager", "Update", 0)->methodPointer;
		INSTALL_HOOK(Update);

		Start_orig = (Start_t)il2cpp_utils::GetMethod("", "GameManager", "Start", 0)->methodPointer;
		INSTALL_HOOK(Start);
	}
};