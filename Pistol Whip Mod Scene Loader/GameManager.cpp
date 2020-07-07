#include "GameManager.hpp"
#include "il2cpp_utils.hpp"
#include "utils.h"
#include "logger.h"
#include "LevelManager.hpp"


namespace GameManager {



	static bool pressed = false;

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
		

		if ((keyState = GetAsyncKeyState(VK_F1)) && pressed == false)// & 0x8000
		{
			LOG("Pressed F1\n");
			pressed = true;
			Il2CppObject* levels = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levels");
			Il2CppObject* lastReleasedScene = il2cpp_utils::GetFieldValue(levels, "lastReleasedScene");
			Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(lastReleasedScene, "maps"));
			Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, 0);//GameMap

			Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messages/LevelLoadRequest");

			msg = il2cpp_functions::object_new(klass);
			il2cpp_utils::RunMethod(msg, ".ctor");
			il2cpp_utils::RunMethod(msg, "Set", map);

			//il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(LevelManager::levelManager()), "OnLevelLoadRequested", msg);

			//il2cpp_utils::SetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levelData", lastReleasedScene);
			il2cpp_utils::SetFieldValue(reinterpret_cast<Il2CppObject*>(self), "map", map);
			il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "PrepAndStartGame");
			il2cpp_utils::RunMethod(reinterpret_cast<Il2CppObject*>(self), "OnStartButton");

			//Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messenger");
			//auto* method = il2cpp_utils::GetMethod(klass, "get_Default", 0);
			//Il2CppObject* Messenger = nullptr;
			//il2cpp_utils::GetFieldValue(Messenger, klass, "defaultMessenger");
			////il2cpp_utils::RunMethod(Messenger, klass, method);
			//il2cpp_utils::RunMethod(Messenger, "Send", map);

		}
		if ( GetAsyncKeyState(VK_F2)) pressed = false;

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