#include "SimpleMusicPlayer.hpp"
#include "utils.h"

namespace SimpleMusicPlayer {

	MAKE_HOOK(Play, void, void* self)
	{
		LOG("SonicBloom.Koreo.Players.SimpleMusicPlayer.Play() hook called\n");
		Play_orig(self);
	}


	MAKE_HOOK(LoadSong, void, void* self, void* koreo, int startSampleTime, int autoPlay)
	{
		LOG("SonicBloom.Koreo.Players.SimpleMusicPlayer.LoadSong(Koreography, int, bool) hook called\n");
		LoadSong_orig(self, koreo, startSampleTime, autoPlay);
	}


	void initHooks(funchook_t* funchookp)
	{
		Play_orig = (Play_t)il2cpp_utils::GetMethod("SonicBloom.Koreo.Players", "SimpleMusicPlayer", "Play", 0)->methodPointer;
		INSTALL_HOOK(Play);

		LoadSong_orig = (LoadSong_t)il2cpp_utils::GetMethod("SonicBloom.Koreo.Players", "SimpleMusicPlayer", "LoadSong", 3)->methodPointer;
		INSTALL_HOOK(LoadSong);

	}


};