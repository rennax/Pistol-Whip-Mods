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

#include "GameObject.hpp"
#include "SongSelectController.hpp"

#include <filesystem>
#include <fstream>
#include <bitset>

namespace fs = std::filesystem;


namespace GameManager {

	void PrepAndStart(Il2CppObject* self, Il2CppObject* level, Il2CppObject* map)
	{
		bool s = false;
		il2cpp_utils::RunMethod(self, "SetModifiers", &s);

		auto klass = il2cpp_utils::GetClassFromName("", "Messages/LevelLoadRequest");
		Il2CppObject* loadRequest = il2cpp_functions::object_new(klass);
		il2cpp_utils::RunMethod(loadRequest, ".ctor");
		il2cpp_utils::RunMethod(loadRequest, "Set", map);
		

		//Get Messenger instance
		klass = il2cpp_utils::GetClassFromName("", "Messenger");
		Il2CppObject* messenger = nullptr;
		il2cpp_utils::RunMethod(&messenger, klass, "get_Default");


		/* Create LevelLoadRequest and send it*/
		const MethodInfo* info = il2cpp_utils::GetMethod("", "Messenger", "Send", 1);
		// Get my generic methodInfo
		const MethodInfo* sendLevelLoad = il2cpp_utils::MakeGeneric(info, { il2cpp_utils::GetClassFromName("", "Messages/LevelLoadRequest") });
		// Call the method
		if (!il2cpp_utils::RunMethod(messenger, sendLevelLoad, loadRequest))
			LOG("WARNING: Failed to run Send(Messages.LevelLoadRequest e)\n");


		/* set leveldata field values */
		float gameStartTime = -1, gameProgress = 0, gameLength = -1;
		il2cpp_utils::RunMethod(&gameStartTime, il2cpp_utils::GetClassFromName("UnityEngine", "Time"), "get_time");
		il2cpp_utils::GetFieldValue(&gameLength, level, "songLength");

		il2cpp_utils::SetFieldValue(self, "gameLength", &gameLength);
		il2cpp_utils::SetFieldValue(self, "gameProgress", &gameProgress);
		il2cpp_utils::SetFieldValue(self, "gameStartTime", &gameStartTime);

		bool playing = true;
		il2cpp_utils::SetFieldValue(self, "playing", &playing);


		/* Create GameStartEvent and send it*/
		klass = il2cpp_utils::GetClassFromName("", "Messages/GameStartEvent");
		Il2CppObject* startEvent = il2cpp_functions::object_new(klass);
		il2cpp_utils::RunMethod(startEvent, ".ctor");
		il2cpp_utils::RunMethod(startEvent, "Set", map);

//		info = il2cpp_utils::GetMethod("", "Messenger", "Send", 1);
		// Get my generic methodInfo
		const MethodInfo* sendGameStart = il2cpp_utils::MakeGeneric(info, { il2cpp_utils::GetClassFromName("", "Messages/GameStartEvent") });
		// Call the method
		if (!il2cpp_utils::RunMethod(messenger, sendGameStart, startEvent))
			LOG("WARNING: Failed to run Send(Messages.GameStartEvent e)\n");

		Il2CppObject* gameStartEvent = il2cpp_utils::GetFieldValue(self, "gameStartEvent");
		il2cpp_utils::RunMethod(gameStartEvent, "Raise");


		//START SONG
		int32_t difficulty = 0;
		il2cpp_utils::GetFieldValue(&difficulty, self, "difficulty");

		Il2CppObject* levels = il2cpp_utils::GetFieldValue(self, "levels");
		Array<Il2CppObject*>* koreoSets = nullptr;
		il2cpp_utils::GetFieldValue(&koreoSets, levels, "koreoSets");
		Il2CppObject* koreoSet = koreoSets->values[0];//Use difficulty

		Il2CppObject* song = il2cpp_utils::GetFieldValue(level, "songSwitch");

		float seekTime = 0;



		il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "MusicManager"), "PlaySong", koreoSet, song, &seekTime);


	}

	static uint32_t (*LoadBank_internal)(char* buff, uint32_t size, uint32_t* outID);
	typedef uint32_t (*LoadBank_internal_t)(char* buff, uint32_t size, uint32_t* outID);

	MAKE_HOOK(OnSceneSelect, void, Il2CppObject* self) {
		LOG("Called GameManager.OnSceneSelect() hook\n");
		OnSceneSelect_orig(self);
	}
	SongSelectController *ctrl;
	MAKE_HOOK(Start, void, Il2CppObject* self) {
		LOG("Called GameManager.Start() hook\n");

		Start_orig(self);
		
		//Il2CppObject* lvlDB;
		//il2cpp_utils::GetFieldValue(&lvlDB, self, "levels");
		//Il2CppString* str;
		//il2cpp_utils::GetFieldValue(&str, lvlDB, "pistolWhipDescription");
		//LOG("LevelDatabase.pistolWhipDescription %s", to_utf8(csstrtostr(str)).c_str());

		//ctrl = SongSelectController::get_Instance();
		AssetBundle::Init();
		
	}


	MAKE_HOOK(UpdateEnemyAttackInterval, void, void* self)
	{
		LOG("GameManager.UpdateEnemyAttackInterval() called \n");
		UpdateEnemyAttackInterval_orig(self);
	}

	LevelData* data = nullptr;
	Il2CppObject* levelData = nullptr;

	static bool pf1 = false, pf2;

	Il2CppObject* msg = nullptr;

	static float progress = 0;
	static float gameLength = 0;
	static float gameTime = 0;

	MAKE_HOOK(Update, void, Il2CppObject* self) {
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


			//int32_t diff = 0;
			//il2cpp_utils::SetFieldValue(reinterpret_cast<Il2CppObject*>(self), "difficulty", &diff);

			//data = new LevelData();
			//std::string version = j["version"];
			//LOG("%s\n", version.c_str());
			//levelData = data->Load(j["levelData"]);

			//
			//Il2CppObject* levels = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			//Il2CppObject* lastReleasedScene = il2cpp_utils::GetFieldValue(levels, "lastReleasedScene");
			//il2cpp_utils::SetFieldValue(levelData, "songSwitch", il2cpp_utils::GetFieldValue(lastReleasedScene, "songSwitch"));
			//Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(levelData, "maps"));
			//Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, 0); //GameMap
			//

			////il2cpp_utils::SetFieldValue(levelData, "sections", il2cpp_utils::GetFieldValue(lastReleasedScene, "sections"));


			//if (!il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "SetLevelInternal", map))
			//	LOG("WARNING: Failed call to GameManager.SetLevelInternal(GameMap)\n");

			//PrepAndStart(reinterpret_cast<Il2CppObject*>(self), levelData, map);

			//Il2CppObject* UIStateCtrl;
			//il2cpp_utils::RunMethod(&UIStateCtrl, il2cpp_utils::GetClassFromName("", "UIStateController"), "get_Instance");
			//il2cpp_utils::RunMethod(UIStateCtrl, "OnSelectStartSongUIButton");
			//il2cpp_utils::RunMethod(UIStateCtrl, "PlaySong");

			il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "DelayedSelectStartFromUI");


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
			
			Il2CppString* trackName = nullptr, * lvlName = nullptr;
			il2cpp_utils::RunMethod(&trackName, trackData, "get_name");
			LOG("TrackData gameobject name: %s\n", to_utf8(csstrtostr(trackName)).c_str());
			il2cpp_utils::RunMethod(&lvlName, lastReleasedScene, "get_name");
			LOG("LevelData gameobject name: %s\n", to_utf8(csstrtostr(lvlName)).c_str());


			Koreography koreography(koreo);
			json j = koreography.Dump();
			std::ofstream o = std::ofstream("Koreography.json");
			o << std::setw(4) << j << std::endl;
			o.close();

			Il2CppObject* lvlDb = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			//Il2CppArray* koreoSets = nullptr;
			//il2cpp_utils::GetFieldValue(koreoSets, lvlDb, "koreoSets");


			//Il2CppObject* frontLotKoreoSet;
			Array<Il2CppObject*>* koreoSets;
			il2cpp_utils::GetFieldValue(&koreoSets, levels, "koreoSets");
			
			
			j.clear();
			for (size_t i = 0; i < 3; i++)
			{
				WwiseKoreographySet koreoSet(koreo, koreoSets->values[i]);
				j["koreoSets"].push_back(koreoSet.Dump());
			}
			o = std::ofstream("WWiseKoreoSetDump0.json");
			o << std::setw(4) << j << std::endl;
			o.close();

			LevelData level(reinterpret_cast<Il2CppObject*>(self), lastReleasedScene);
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
		//if (pf1 == true)
		//{
		//	Il2CppString* str;
		//	Il2CppObject* player = nullptr; //IKoreographedPlayer
		//	il2cpp_utils::GetFieldValue(&player, il2cpp_utils::GetClassFromName("", "MusicManager"), "player");
		//	if (player != nullptr)
		//	{
		//		if (il2cpp_utils::RunMethod(&str, player, "GetCurrentClipName"))
		//			LOG("MusicManager.player.GetCurrentClipName = %s\n", to_utf8(csstrtostr(str)).c_str());
		//		str = nullptr;
		//		il2cpp_utils::GetFieldValue(&str, il2cpp_utils::GetClassFromName("", "MusicManager"), "songName");
		//		if (str != nullptr)
		//		{
		//			LOG("MusicManager.songName = %s\n", to_utf8(csstrtostr(str)).c_str());
		//		}

		//	}
		//	

		//	
		//}

		//bool playing;
		//il2cpp_utils::GetFieldValue(&playing, self, "playing");
		//if (playing)
		//{
		//	static int t = 0;
		//	if (t % 60 == 0)
		//	{
		//		il2cpp_utils::GetFieldValue(&gameLength, self, "gameLength");
		//		il2cpp_utils::GetFieldValue(&gameTime, self, "gameTime");
		//		LOG("gameTime: %f, gameProgress: %f, gameLength: %f\n", gameTime, progress, gameLength);
		//	}
		//	t++;
		//}


		Update_orig(self);
	}


	MAKE_HOOK(get_GameProgress, float)
	{
		progress = get_GameProgress_orig();
		//if (pf1 == true)
		//{
		//	LOG("GameManager::get_GameProgress() = %f\n", progress);
		//}
		return progress;
	}

	MAKE_HOOK(StopMovement, void, void* self)
	{
		LOG("PlayerMovementManager::StopMovement()\n");
		StopMovement_orig(self);
	}

	MAKE_HOOK(OnSongStop, void, void* self)
	{
		LOG("GameManager::OnSongStop()\n");
		StopMovement_orig(self);
	}

	MAKE_HOOK(LateUpdate, void, void* self)
	{
		LateUpdate_orig(self);

	}

	MAKE_HOOK(LoadKoreography, void, Il2CppObject* self, Il2CppObject* koreo)
	{
		LOG("SonicBloom.Koreo.Koreographer.LoadKoreography()\n");
		LoadKoreography_orig(self, koreo);
	}

	MAKE_HOOK(GetSourcePlayPosition, int32_t, uint32_t eventID, int32_t& out_pos, bool extrapolate)
	{
		int32_t res = GetSourcePlayPosition_orig(eventID, out_pos, extrapolate);
		static int t = 0;
		if (t%60 == 0)
		{
			LOG("AkSoundEngine.GetSourcePlayPosition() called, eventID %u, position %d, extrapolate %s, returned %d\n", eventID, out_pos, extrapolate ? "true":"false", res);
		}
		t++;
		return res;
	}

	MAKE_HOOK(SetState, int32_t, uint32_t in_stateGroup, uint32_t in_state)
	{
		int32_t res = SetState_orig(in_stateGroup, in_state);
		LOG("AkSoundEngine.SetState() called, in_stateGroup %u, in_state %u, returned %d\n", in_stateGroup, in_state, res);
		return res;
	}

	MAKE_HOOK(SeekOnEvent, int32_t, Il2CppString* in_pszEventName, Il2CppObject* in_gameObjectID, int in_iPosition)
	{
		int32_t res = SeekOnEvent_orig(in_pszEventName, in_gameObjectID, in_iPosition);
		LOG("AkSoundEngine.SeekOnEvent() called, ..., ..., timeMS %d, returned %d\n", in_iPosition, res);
		return res;
	}

	MAKE_HOOK(Load, uint32_t, Il2CppString* name, int32_t id, uint32_t * out) {
		uint32_t res = Load_orig(name, id, out);
		LOG("AkSoundEngine.Load() called, Result=%u, mempoolid=%d, bankID=%u, pszString=%s\n", res, id, *out, to_utf8(csstrtostr(name)).c_str());
		return res;
	}



	MAKE_HOOK(UIElement, void, void* self)
	{
		LOG("VRLaserPointer.Awake called\n");
		LOG("Awaking VRLaserPointer before we get the layer Mask");
		UIElement_orig(self);
		struct LayerMask {
			int32_t m_Mask;
		};
		LayerMask mask;
		il2cpp_utils::GetFieldValue(&mask, reinterpret_cast<Il2CppObject*>(self), "allowedLayers");
		LOG("Mask %d\n", mask.m_Mask);
		std::stringstream ss;
		ss << std::bitset<32>(mask.m_Mask);
		LOG("Binary mask: %s\n", ss.str().c_str());
		for (size_t i = 0; i < 32; i++)
		{
			Il2CppString* layerName;
			il2cpp_utils::RunMethod(&layerName, il2cpp_utils::GetClassFromName("UnityEngine", "LayerMask"), "LayerToName", &i);
			LOG("Layer %d has the name: %s\n", i, to_utf8(csstrtostr(layerName)).c_str());
		}

	}

	MAKE_HOOK(HoverEnter, void, void* self)
	{
		LOG("CHUI_TriggerEvents.OnHoverEnter() called\n");
		HoverEnter_orig(self);
	}

	MAKE_HOOK(Click, void, void* self)
	{
		LOG("CHUI_TriggerEvents.OnClick called\n");
		Click_orig(self);
	}

	MAKE_HOOK(HoverStay, void, void* self)
	{
		LOG("CHUI_TriggerEvents.OnHoverStay called\n");
		HoverStay_orig(self);
	}

	MAKE_HOOK(HoverExit, void, void* self)
	{
		LOG("CHUI_TriggerEvents.HoverExit called\n");
		HoverExit_orig(self);
	}


	void initHooks(funchook_t* funchookp)
	{
		LOG("GameManager::initHooks()\n");
		
		//UIElement_orig = (UIElement_t)il2cpp_utils::GetMethod("", "VRLaserPointer", "Awake", 0)->methodPointer;
		//INSTALL_HOOK(UIElement);

		//HoverEnter_orig = (HoverEnter_t)il2cpp_utils::GetMethod("", "CHUI_TriggerEvents", "OnHoverEnter", 0)->methodPointer;
		//INSTALL_HOOK(UIElement);

		//Click_orig = (Click_t)il2cpp_utils::GetMethod("", "CHUI_TriggerEvents", "OnClick", 0)->methodPointer;
		//INSTALL_HOOK(Click);

		//HoverStay_orig = (HoverStay_t)il2cpp_utils::GetMethod("", "CHUI_TriggerEvents", "OnHoverStay", 0)->methodPointer;
		//INSTALL_HOOK(HoverStay);

		//HoverExit_orig = (HoverExit_t)il2cpp_utils::GetMethod("", "CHUI_TriggerEvents", "OnHoverExit", 0)->methodPointer;
		//INSTALL_HOOK(HoverExit);



		
		Update_orig = (Update_t)il2cpp_utils::GetMethod("", "GameManager", "Update", 0)->methodPointer;
		INSTALL_HOOK(Update);

		Start_orig = (Start_t)il2cpp_utils::GetMethod("", "GameManager", "Start", 0)->methodPointer;
		INSTALL_HOOK(Start);

		//UpdateEnemyAttackInterval_orig = (UpdateEnemyAttackInterval_t)il2cpp_utils::GetMethod("", "GameManager", "UpdateEnemyAttackInterval", 0)->methodPointer;
		//INSTALL_HOOK(UpdateEnemyAttackInterval);

		OnSongStop_orig = (OnSongStop_t)il2cpp_utils::GetMethod("", "GameManager", "OnSongStop", 0)->methodPointer;
		INSTALL_HOOK(OnSongStop);

		StopMovement_orig = (StopMovement_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "StopMovement", 0)->methodPointer;
		INSTALL_HOOK(StopMovement);

		//get_GameProgress_orig = (get_GameProgress_t)il2cpp_utils::GetMethod("", "GameManager", "get_GameProgress", 0)->methodPointer;
		//INSTALL_HOOK(get_GameProgress);

		

		//LoadKoreography_orig = (LoadKoreography_t)il2cpp_utils::GetMethod("SonicBloom.Koreo", "Koreographer", "LoadKoreography", 1)->methodPointer;
		//INSTALL_HOOK(LoadKoreography);

		//GetSourcePlayPosition_orig = (GetSourcePlayPosition_t)il2cpp_utils::GetMethod("", "AkSoundEngine", "GetSourcePlayPosition", 3)->methodPointer;
		//INSTALL_HOOK(GetSourcePlayPosition);

		//SetState_orig = (SetState_t)il2cpp_utils::GetMethod("", "AkSoundEngine", "SetState", 2)->methodPointer;
		//INSTALL_HOOK(SetState);

		//SeekOnEvent_orig = (SeekOnEvent_t)il2cpp_utils::GetMethod("", "AkSoundEngine", "SeekOnEvent", 3)->methodPointer;
		//INSTALL_HOOK(SeekOnEvent);

		//LateUpdate_orig = (LateUpdate_t)il2cpp_utils::GetMethod("", "MusicManager", "LateUpdate", 0)->methodPointer;
		//INSTALL_HOOK(LateUpdate);

		/*get_time_orig = (get_time_t)il2cpp_utils::GetMethod("UnityEngine", "Time", "get_time", 0)->methodPointer;
		INSTALL_HOOK(get_time);*/

		/*get_difficulty_orig = (get_difficulty_t)il2cpp_utils::GetMethod("", "GameMap", "get_difficulty", 0)->methodPointer;
		INSTALL_HOOK(get_difficulty);*/
	}
};

//	LoadBank_internal = (LoadBank_internal_t)il2cpp_functions::resolve_icall("AkSoundEngine::LoadBank(System.IntPtr, System.UInt32, System.UInt32)");
//if (!fs::exists("Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/Song.bnk"))
//{
//	LOG("%s does not exists\n", "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/Song.bnk\n");
//	return;
//}
//std::ifstream file("Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/Song.bnk", std::ios::ate | std::ios::binary);
//if (file.is_open())
//{
//	uint32_t size = file.tellg(); // Might not always give the correct size?
//	file.seekg(0, std::ios::beg);
//	char* buffer = new char[size];
//	file.read(buffer, size);
//	uint32_t bankID;
//	uint32_t res;
//	//int32_t res = LoadBank_internal(buffer, size, &bankID);
//	il2cpp_utils::RunMethod(&res, il2cpp_utils::GetClassFromName("", "AkSoundEngine"), "LoadBank", buffer, &size, &bankID);
//	
//	LOG("Called AkSoundEngine.Load(.., .., ..) bank id is %u, returned %d\n", bankID, res);
//}
//else
//	LOG("Couldn't open %s\n", "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/Song.bnk\n");

//uint32_t version;
//il2cpp_utils::RunMethod(&version, il2cpp_utils::GetClassFromName("", "AkSoundEngine"), "get_AK_SOUNDBANK_VERSION");
//LOG("version %u\n", version);

//std::string name = "Song";
//bool decodeBank = false;
//bool saveDecodedBank = false;
//int32_t memPoolID = -1; //AK_DEFAULT_POOL_ID 
//uint32_t bankID;
//uint32_t res;
////il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "AkBankManager"), "DoUnloadBanks");
////il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "AkBankManager"), "LoadBank", il2cpp_utils::createcsstr("Init2"), &decodeBank, &saveDecodedBank);
//il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "AkBankManager"), "LoadBank", il2cpp_utils::createcsstr("Init2"), &decodeBank, &saveDecodedBank);
//il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "AkBankManager"), "LoadBank", il2cpp_utils::createcsstr("Song"), &decodeBank, &saveDecodedBank);
////il2cpp_utils::RunMethod(&res, il2cpp_utils::GetClassFromName("", "AkSoundEngine"), "LoadBank", il2cpp_utils::createcsstr(name), &memPoolID, &bankID);
////LOG("Attempt to load bank %s, with mempoolID %u, we got result %u and bankID %u\n", name.c_str(), memPoolID, res, bankID);
//
////il2cpp_utils::RunMethod(&res, il2cpp_utils::GetClassFromName("", "AkSoundEngine"), "SetState", il2cpp_utils::createcsstr("MusicState"), il2cpp_utils::createcsstr("Religion"));
////LOG("RES %u", res);'
////Il2CppObject* initSettings = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "AkInitSettings"));
////il2cpp_utils::RunMethod(initSettings, ".ctor");
////il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("", "AkSoundEngine"), "GetDefaultInitSettings", initSettings);
////uint32_t poolSize;
////il2cpp_utils::RunMethod(&poolSize, initSettings, "get_uDefaultPoolSize");
////LOG("Default wwise pool size %u\n", poolSize); // 16777216