#include "LevelManager.hpp"
#include "utils.h"
#include "il2cpp_utils.hpp"
#include "logger.h"
#include "GeoSet.hpp"
#include "Mesh.hpp"
#include "AudioClip.hpp"
#include "TrackData.hpp"
#include "AssetBundle.hpp"
#include "LevelData.hpp"

#include <vector>

namespace LevelManager {

	void* lvlmng = nullptr;
	MAKE_HOOK(OnEnable, void, void* self) {
		lvlmng = self;
		OnEnable_orig(self);
	}

	void* levelManager() {
		return lvlmng;
	}


	MAKE_HOOK(SpawnGeoLevel, bool, Il2CppObject *level, Il2CppObject *lvlAssetDB, int minLOD)
	{
		LOG("LevelManager::SpawnGeoLevel()\n");
		return SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);
	}

	MAKE_HOOK(LoadLevel, void, void* self, Il2CppObject* level)
	{
		LOG("LevelManager::LoadLevel()\n");
		LoadLevel_orig(self, level);
	}

	/*-------------->> following hooks are for debug purpose <<-------------*/
	MAKE_HOOK(OnLevelChange, void, void* self, void* e)
	{
		LOG("PlayerMovementManager::OnLevelChange()\n");
		OnLevelChange_orig(self, e);
	}

	MAKE_HOOK(OnGameStart, void, void* self)
	{
		LOG("PlayerMovementManager::OnGameStart()\n");
		OnGameStart_orig(self);
	}

	MAKE_HOOK(OnSongStop, void, void* self)
	{
		LOG("PlayerMovementManager::OnSongStop()\n");
		OnSongStop_orig(self);
	}

	MAKE_HOOK(OnGameEnd, void, void* self)
	{
		LOG("PlayerMovementManager::OnGameEnd()\n");
		OnGameEnd_orig(self);
	}

	MAKE_HOOK(StartMovement, void, void* self)
	{
		LOG("PlayerMovementManager::StartMovement()\n");
		StartMovement_orig(self);
	}

	MAKE_HOOK(StopMovement, void, void* self)
	{
		LOG("PlayerMovementManager::StopMovement()\n");
		StopMovement_orig(self);
	}


	MAKE_HOOK(get_name, Il2CppString*, void* self)
	{
		
		Il2CppString* name = get_name_orig(self);
		LOG("GameMap::get_name() : %s\n", to_utf8(csstrtostr(name)).c_str());

		return name;
	}


	void initHooks(funchook_t* funchookp)
	{
		LOG("LevelManager::initHooks()\n");
		SpawnGeoLevel_orig = (SpawnGeoLevel_t)il2cpp_utils::GetMethod("", "LevelManager", "SpawnLevelGeo", 3)->methodPointer;
		INSTALL_HOOK(SpawnGeoLevel);

		LoadLevel_orig = (LoadLevel_t)il2cpp_utils::GetMethod("", "LevelManager", "LoadLevel", 1)->methodPointer;
		INSTALL_HOOK(LoadLevel);

		OnEnable_orig = (OnEnable_t)il2cpp_utils::GetMethod("", "LevelManager", "OnEnable", 0)->methodPointer;
		INSTALL_HOOK(OnEnable);

		
		//OnGameStart_orig = (OnGameStart_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnGameStart", 0)->methodPointer;
		//INSTALL_HOOK(OnGameStart);

		OnSongStop_orig = (OnSongStop_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnSongStop", 0)->methodPointer;
		INSTALL_HOOK(OnSongStop);

		OnGameEnd_orig = (OnEnable_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnGameEnd", 0)->methodPointer;
		INSTALL_HOOK(OnGameEnd);

		StartMovement_orig = (StartMovement_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "StartMovement", 0)->methodPointer;
		INSTALL_HOOK(OnEnable);

		StopMovement_orig = (StopMovement_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "StopMovement", 0)->methodPointer;
		INSTALL_HOOK(StopMovement);

		OnLevelChange_orig = (OnLevelChange_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnLevelChange", 1)->methodPointer;
		INSTALL_HOOK(OnLevelChange);

		OnLevelChange_orig = (OnLevelChange_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnLevelChange", 1)->methodPointer;
		INSTALL_HOOK(OnLevelChange);

		//get_name_orig = (get_name_t)il2cpp_utils::GetMethod("", "GameMap", "get_name",0 )->methodPointer;
		//INSTALL_HOOK(get_name);
		
	}

};
