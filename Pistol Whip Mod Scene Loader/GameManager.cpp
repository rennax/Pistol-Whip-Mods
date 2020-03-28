#include "GameManager.hpp"
#include "il2cpp_utils.hpp"
#include "utils.h"
#include "logger.h"

namespace GameManager {

	MAKE_HOOK(OnSceneSelect, void, void* self) {
		LOG("Called GameManager.OnSceneSelect() hook");
		OnSceneSelect_orig(self);
	}

	void initHooks(funchook_t* funchookp)
	{
		LOG("GameManager::initHooks()\n");
		 
		OnSceneSelect_orig = (OnSceneSelect_t)il2cpp_utils::GetMethod("", "GameManager", "OnSceneSelect", 0)->methodPointer;
		INSTALL_HOOK(OnSceneSelect);
	}
};