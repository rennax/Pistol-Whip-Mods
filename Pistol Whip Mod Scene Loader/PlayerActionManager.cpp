#include "PlayerActionManager.hpp"
#include "utils.h"

MAKE_HOOK(OnGameStart, void, void* self)
{
	LOG("PlayerActionManager::OnGameStart() called");
	return OnGameStart_orig(self);
}

void PlayerActionManager::initHooks(funchook_t* funchookp)
{
	OnGameStart_orig = (OnGameStart_t)il2cpp_utils::GetMethod("", "PlayerActionManager", "OnGameStart", 0)->methodPointer;
	INSTALL_HOOK(OnGameStart);
}
