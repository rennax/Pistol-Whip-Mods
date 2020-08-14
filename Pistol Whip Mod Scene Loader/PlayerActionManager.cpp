#include "PlayerActionManager.hpp"
#include "utils.h"

MAKE_HOOK(OnGameStart, void, void* self)
{
	LOG("PlayerActionManager::OnGameStart() called\n");
	OnGameStart_orig(self);
}

MAKE_HOOK(PlayerMovementManager_OnGameStart, void, void* self)
{
	LOG("PlayerMovementManager.OnGameStart() called\n");
	PlayerMovementManager_OnGameStart_orig(self);
}

MAKE_HOOK(Quantizer_OnGameStart, void, void* self)
{
	LOG("Quantizer.OnGameStart() called\n");
	Quantizer_OnGameStart_orig(self);
}

MAKE_HOOK(SpawningComplete, void, void* self)
{
	LOG("PlayerActionManager.OnSpawningComplete()");
	SpawningComplete_orig(self);
}

MAKE_HOOK(ResetPlayer, void, void* self)
{
	LOG("PlayerMovementManager.ResetPlayer()");
	ResetPlayer_orig(self);
}



void PlayerActionManager::initHooks(funchook_t* funchookp)
{
	PlayerMovementManager_OnGameStart_orig = (PlayerMovementManager_OnGameStart_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "OnGameStart", 0)->methodPointer;
	INSTALL_HOOK(PlayerMovementManager_OnGameStart);

	//Quantizer_OnGameStart_orig = (Quantizer_OnGameStart_t)il2cpp_utils::GetMethod("", "Quantizer", "OnGameStart", 0)->methodPointer;
	//INSTALL_HOOK(Quantizer_OnGameStart);

	OnGameStart_orig = (OnGameStart_t)il2cpp_utils::GetMethod("", "PlayerActionManager", "OnGameStart", 0)->methodPointer;
	INSTALL_HOOK(OnGameStart);

	SpawningComplete_orig = (SpawningComplete_t)il2cpp_utils::GetMethod("", "PlayerActionManager", "OnSpawningComplete", 0)->methodPointer;
	INSTALL_HOOK(SpawningComplete);

	ResetPlayer_orig = (ResetPlayer_t)il2cpp_utils::GetMethod("", "PlayerMovementManager", "ResetPlayer", 0)->methodPointer;
	INSTALL_HOOK(ResetPlayer);
}
