#include "MultiMusicPlayer.hpp"
#include "utils.h"

namespace MultiMusicPlayer {

	MAKE_HOOK(Play, void, void* self)
	{
		LOG("SonicBloom.Koreo.Players.MultiMusicPlayer.Play() hook called\n");
		Play_orig(self);
	}


	MAKE_HOOK(LoadSong, void, void* self, void* layers, int startSampleTime, bool autoPlay)
	{
		LOG("SonicBloom.Koreo.Players.MultiMusicPlayer.LoadSong(List<MusicLayers>, int, bool) hook called\n");
		LoadSong_orig(self, layers, startSampleTime, autoPlay);
	}

	MAKE_HOOK(LoadKoreographyAndStart, void, void* self, int startSampleTime, bool autoPlay)
	{
		LOG("SonicBloom.Koreo.Players.MultiMusicPlayer.LoadKoreographyAndStart(int, bool) hook called\n");
		LoadKoreographyAndStart_orig(self, startSampleTime, autoPlay);
	}


	void initHooks(funchook_t* funchookp)
	{
		Play_orig = (Play_t)il2cpp_utils::GetMethod("SonicBloom.Koreo.Players", "MultiMusicPlayer", "Play", 0)->methodPointer;
		INSTALL_HOOK(Play);

		LoadSong_orig = (LoadSong_t)il2cpp_utils::GetMethod("SonicBloom.Koreo.Players", "MultiMusicPlayer", "LoadSong", 3)->methodPointer;
		INSTALL_HOOK(LoadSong);

		LoadKoreographyAndStart_orig = (LoadKoreographyAndStart_t)il2cpp_utils::GetMethod("SonicBloom.Koreo.Players", "MultiMusicPlayer", "LoadKoreographyAndStart", 2)->methodPointer;
		INSTALL_HOOK(LoadKoreographyAndStart);

	}


};