#include "SongSelectionUIController.hpp"

#include "utils.h"
#include "il2cpp_utils.hpp"
#include "LevelDatabase.hpp"
#include "logger.h"


namespace SongSelectionUIController {

	MAKE_HOOK(SetSongSelectionState, void, void* self)
	{
		LOG("SongSelectionUIController.SetSongSelectionState() hook called\n");
		SetSongSelectionState_orig(self);
	}

	MAKE_HOOK(UpdateSelectedSong, void, void* self, void* p_songPanelCont)
	{
		LOG("SongSelectionUIController.UpdatedSelectedSong() hook called\n");
		UpdateSelectedSong_orig(self, p_songPanelCont);

		// Try to log the levelDataIndex
		int levelDataIndex = -1;
		il2cpp_utils::GetFieldValue(&levelDataIndex, reinterpret_cast<Il2CppObject*>(p_songPanelCont), "levelDataIndex");
		LOG("levelDataIndex: %d\n", levelDataIndex);

		auto levelDatabase = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levelDB");
		LevelDatabase::LevelCount(levelDatabase);
		//DublicateLevelLastLevel(levelDatabase);
		//LevelDatabase::LevelCount(levelDatabase);
	}



	void initHooks(funchook_t* funchookp)
	{
		SetSongSelectionState_orig = (SetSongSelectionState_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "SetSongSelectionState", 0)->methodPointer;
		INSTALL_HOOK(SetSongSelectionState);

		UpdateSelectedSong_orig = (UpdateSelectedSong_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "UpdateSelectedSong", 1)->methodPointer;
		INSTALL_HOOK(UpdateSelectedSong);
	}

};