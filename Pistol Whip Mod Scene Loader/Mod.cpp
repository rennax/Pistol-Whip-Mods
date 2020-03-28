// SampleMod.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Mod.h"
#include "il2cpp_functions.hpp"
#include "il2cpp_utils.hpp"
#include "utils-functions.hpp"
#include <string>
#include "logger.h"

//All classes that are hooked
#include "GameManager.hpp"
#include "LevelDatabase.hpp"
#include "SongSelectionUIController.hpp"
#include "SceneManager.hpp"
#include "LevelSelectTrigger.hpp"
#include "LevelManager.hpp"

extern "C" { // name mangle 
#include <funchook.h>
}



  
funchook_t* funchook;

SAMPLEMOD_API int load(HANDLE logHandle, HMODULE gameAssembly) {
	init_logger(logHandle);
	LOG("\nBeginning load!\n");
	il2cpp_functions::Init(gameAssembly);
	// Install hooks onto gameAssembly here
	auto base = (uint64_t)gameAssembly;
	LOG("GameAssembly.dll base: %lx\n", base);
	funchook = funchook_create();

	GameManager::initHooks(funchook);
	LevelDatabase::initHooks(funchook);
	SongSelectionUIController::initHooks(funchook);
	SceneManager::initHooks(funchook);
	LevelSelectTrigger::initHooks(funchook);
	LevelManager::initHooks(funchook);


	int rv = funchook_install(funchook, 0);
	if (rv != 0) {
		LOG("ERROR: failed to install open and fopen hooks. (%s)\n", funchook_error_message(funchook));
		return -1;
	}	

	LOG("Installed hooks!!\n");
	return 0;
}
