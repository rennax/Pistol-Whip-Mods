#include "LevelSelectTrigger.hpp"
#include "utils.h"
#include "il2cpp_utils.hpp"
#include "logger.h"
//Pistol Whip GameManager : Singleton<GameManager>
namespace LevelSelectTrigger {

MAKE_HOOK(ctor, void, void *self)
{
	LOG("Called LevelSelect.ctor() hook!\n");
	ctor_orig(self);
	//LOG("Creating local instance of LevelSelectTrigger.OnLevelSelect!\n");
}

MAKE_HOOK(OnLevelSelect, void, void* self, void *e)
{
	LOG("Called LevelSelectTrigger.OnLevelSelect() hook!\n");
	OnLevelSelect_orig(self, e);
	
	/*if(!onLevelSelect)
		onLevelSelect = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "onLevelSelect");*/
}




void initHooks(funchook_t* funchookp)
{
	LOG("LevelSelectTrigger::initHooks()\n");
	//ctor_orig = (ctor_t)il2cpp_utils::GetMethod("", "LevelSelectTrigger", ".ctor", 0)->methodPointer;;
	//INSTALL_HOOK(ctor);

	//OnLevelSelect_orig = (OnLevelSelect_t)il2cpp_utils::GetMethod("", "LevelSelectTrigger", "OnLevelSelect", 1)->methodPointer;;
	//INSTALL_HOOK(OnLevelSelect);
}
};