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

#include "WwiseKoreographySet.hpp"
#include "TempoSectionDef.hpp"
#include "Koreography.hpp"

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
		{
			LOG("Pressed F1\n");
			pf1 = true;
			

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
			
			//Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messages/LevelLoadRequest");
			/*msg = il2cpp_functions::object_new(klass);
			il2cpp_utils::RunMethod(msg, ".ctor");
			il2cpp_utils::RunMethod(msg, "Set", map);*/

			//il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(LevelManager::levelManager()), "OnLevelLoadRequested", msg);

			il2cpp_utils::SetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levelData", levelData);
			il2cpp_utils::SetFieldValue(reinterpret_cast<Il2CppObject*>(self), "map", map);
			//il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "LoadLevel");
			//il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "StartSong");
			//il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "OnRestartGame");
			il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "OnStartButton");

			//Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messenger");
			//auto* method = il2cpp_utils::GetMethod(klass, "get_Default", 0);
			//Il2CppObject* Messenger = nullptr;
			//il2cpp_utils::GetFieldValue(Messenger, klass, "defaultMessenger");
			////il2cpp_utils::RunMethod(Messenger, klass, method);
			//il2cpp_utils::RunMethod(Messenger, "Send", map);

		}
		else if (GetAsyncKeyState(VK_F2) && pf2 == false) 
		{
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
			//uint32_t koreoSetsSize = il2cpp_functions::array_length(koreoSets);
			//LOG("LevelDatabase.koreoSets.size is %u\n", koreoSetsSize);
			//if (koreoSetsSize > 0)
			//{
			//	WwiseKoreographySet koreoSet(koreo);
			//	json j = koreoSet.Dump();
			//	std::ofstream o = std::ofstream("WWiseKoreosetDump.json");
			//	o << std::setw(4) << j << std::endl;
			//}
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