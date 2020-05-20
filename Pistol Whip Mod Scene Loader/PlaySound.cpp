#include "PlaySound.hpp"
#include "utils.h"

namespace ValvePlaySound {

	MAKE_HOOK(Play, void, void* self)
	{
		LOG("Valve.VR.InteractionSystem.PlaySound.Play() hook called\n");
		Play_orig(self);
	}


	MAKE_HOOK(PlayOneShotSound, Il2CppObject*, void* self)
	{
		LOG("Valve.VR.InteractionSystem.PlaySound.PlayOneShotSound() hook called\n");
		return PlayOneShotSound_orig(self);
	}


	MAKE_HOOK(PlayLooping, Il2CppObject*, void* self)
	{
		LOG("Valve.VR.InteractionSystem.PlaySound.PlayOneShotSound() hook called\n");
		return PlayLooping_orig(self);
	}


	void initHooks(funchook_t* funchookp)
	{
		Play_orig = (Play_t)il2cpp_utils::GetMethod("Valve.VR.InteractionSystem", "PlaySound", "Play", 0)->methodPointer;
		INSTALL_HOOK(Play);

		PlayOneShotSound_orig = (PlayOneShotSound_t)il2cpp_utils::GetMethod("Valve.VR.InteractionSystem", "PlaySound", "PlayOneShotSound", 0)->methodPointer;
		INSTALL_HOOK(PlayOneShotSound);

		PlayLooping_orig = (PlayLooping_t)il2cpp_utils::GetMethod("Valve.VR.InteractionSystem", "PlaySound", "PlayLooping", 0)->methodPointer;
		INSTALL_HOOK(PlayLooping);

	}


};