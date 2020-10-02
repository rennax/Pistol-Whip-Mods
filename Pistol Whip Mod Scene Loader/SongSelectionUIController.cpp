#include "SongSelectionUIController.hpp"

#include "utils.h"
#include "il2cpp_utils.hpp"
#include "LevelDatabase.hpp"
#include "logger.h"
#include "List.hpp"
#include "GameObject.hpp"
#include "LevelData.hpp"
#include "Sprite.hpp"
#include "CustomLevelDatabase.hpp"

using namespace CSharp;


namespace SongSelectionUIController {



	CustomLevelDatabase* database;


	void UpdateSongInfoPanel(Il2CppObject* self, Level& level);
	void Mock_UpdateSelectedSong(Il2CppObject* self, Il2CppObject* songPanel);
	void EnableDifficultyIcons(Level& level, Il2CppObject* songSelectionUIController);
	void SetDifficulty(Difficulty difficulty);


	MAKE_HOOK(Start, Il2CppObject*, Il2CppObject* self)
	{


		Il2CppObject* ret = Start_orig(self);
		database = new CustomLevelDatabase(self);
		//AddPageIndicator(self);
		//AddTestSong(self);
		return ret;
	}


	void UpdateSongInfoPanel(Il2CppObject* self, Level& level)
	{
		AlbumArtMetadata albumArt = level.GetAlbumArt();
		Il2CppObject* songInfo = il2cpp_utils::GetFieldValue(self, "songInfoUI");

		Il2CppObject* songTitle = il2cpp_utils::GetFieldValue(songInfo, "songTitle");
		il2cpp_utils::RunMethod(songTitle, "set_text", level.GetSongName());

		Il2CppObject* artist = il2cpp_utils::GetFieldValue(songInfo, "artist");
		il2cpp_utils::RunMethod(artist, "set_text", albumArt.songArtists);

		Il2CppObject* tempo = il2cpp_utils::GetFieldValue(songInfo, "tempo");
		il2cpp_utils::RunMethod(tempo, "set_text", albumArt.tempo);

		Il2CppObject* songLength = il2cpp_utils::GetFieldValue(songInfo, "songLength");
		float length;
		il2cpp_utils::GetFieldValue(&length, level.GetLevelData(), "songLength");
		il2cpp_utils::RunMethod(songLength, "set_text", il2cpp_utils::createcsstr(std::to_string(length)));

		Il2CppObject* enemyCount = il2cpp_utils::GetFieldValue(songInfo, "enemyCount");
		il2cpp_utils::RunMethod(enemyCount, "set_text", il2cpp_utils::createcsstr(std::to_string(-1)));

		Il2CppObject* personalBest = il2cpp_utils::GetFieldValue(songInfo, "personalBest");
		il2cpp_utils::RunMethod(personalBest, "set_text", il2cpp_utils::createcsstr(std::to_string(-1)));
	}

	//for class SongSelectionUIController
	void Mock_UpdateSelectedSong(Il2CppObject* self, Il2CppObject* songPanel)
	{

		bool active = true, inactive = false;

		auto lastSongPanelSelected = il2cpp_utils::GetFieldValue(self, "lastSongPanelSelected");
		if (lastSongPanelSelected != nullptr)
		{
			il2cpp_utils::RunMethod(lastSongPanelSelected, "SetSelectionOutlineState", &inactive);
		}

		auto lrgAlbumArt = il2cpp_utils::GetFieldValue(self, "lrgAlbumArt");
		auto sprite = il2cpp_utils::GetFieldValue(il2cpp_utils::GetFieldValue(songPanel, "songImage"), "m_Sprite");
		il2cpp_utils::RunMethod(lrgAlbumArt, "set_sprite", sprite);

		auto startBtn = il2cpp_utils::GetFieldValue(self, "startSongUIButton");
		il2cpp_utils::RunMethod(startBtn, "SetActive", &active);


	/*	auto rightTrainingPosterPanel = il2cpp_utils::GetFieldValue(self, "rightTrainingPosterPanel");
		il2cpp_utils::RunMethod(rightTrainingPosterPanel, "set_enabled", &active);*/

		auto songInfoCanvas = il2cpp_utils::GetFieldValue(self, "songInfoCanvas");
		il2cpp_utils::RunMethod(songInfoCanvas, "set_enabled", &active);


		//il2cpp_utils::RunMethod(self, "SelectedEasyDifficulty");

		auto selectionOutline = il2cpp_utils::GetFieldValue(songPanel, "selectionOutline");
		if (selectionOutline != nullptr)
		{
			Il2CppObject* go;
			il2cpp_utils::RunMethod(&go, selectionOutline, "get_gameObject");
			il2cpp_utils::RunMethod(go, "SetActive", &active);
		}

	}

	void EnableDifficultyIcons(Level& level, Il2CppObject* songSelectionUIController)
	{
		Array<Il2CppObject*>* difficultyUIPanels = reinterpret_cast<Array<Il2CppObject*>*>(
			il2cpp_utils::GetFieldValue(songSelectionUIController, "difficultyUIPanels")
			);

		for (size_t i = 0; i < difficultyUIPanels->Length(); i++)
		{
			bool isSelectable = false;
			il2cpp_utils::RunMethod(difficultyUIPanels->values[i], "SetSelectableState", &isSelectable);
		}

		for (size_t i = 0; i < level.GetDifficulties().size(); i++)
		{
			bool isSelectable = true;
			Difficulty diff = level.GetDifficulties()[i];
			il2cpp_utils::RunMethod(difficultyUIPanels->values[static_cast<int32_t>(diff)], "SetSelectableState", &isSelectable);
		}
	}

	void SetDifficulty(Difficulty difficulty)
	{
		Il2CppObject* gameManager;
		if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
			LOG("WARNING: Failed to get instance of GameManager\n");

		il2cpp_utils::SetFieldValue(gameManager, "difficulty", &difficulty);
		Level level = database->GetLevelAtLevelIndex(database->CurrentIndex());
		Il2CppObject* map = level.GetGameMap(difficulty);
		il2cpp_utils::RunMethod(gameManager, "SetLevelInternal", map);
	}
	
	
	MAKE_HOOK(OnClickSong, void, Il2CppObject* self)
	{
		static auto canvasGetGameObjectProp = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Canvas"), "gameObject");
		int32_t levelDataIndex;
		il2cpp_utils::GetFieldValue(&levelDataIndex, self, "levelDataIndex");
		database->CurrentIndex(levelDataIndex);
		if (levelDataIndex > 18) //Get value from levelDatabase
		{
			//Custom map!
			LOG("You clicked on a custom song!\n");

			Level level = database->GetLevelAtLevelIndex(levelDataIndex);
			Il2CppObject* levelData = level.GetLevelData();


			Il2CppObject* songSelectionUIController = il2cpp_utils::GetFieldValue(self, "parent");

			Il2CppObject* songInfoCanvas = il2cpp_utils::GetFieldValue(songSelectionUIController, "songInfoCanvas");
			Il2CppObject* songInfoCanvasGO = nullptr;
			il2cpp_utils::RunMethod(&songInfoCanvasGO, songInfoCanvas, canvasGetGameObjectProp);
			
			Il2CppObject* rightTrainingPosterPanel = il2cpp_utils::GetFieldValue(songSelectionUIController, "rightTrainingPosterPanel");
			Il2CppObject* rightTrainingPosterPanelGO = nullptr;
			il2cpp_utils::RunMethod(&rightTrainingPosterPanelGO, rightTrainingPosterPanel, canvasGetGameObjectProp);

			bool setInfoActive = true, rightTrainingPoster = true;
			

			il2cpp_utils::RunMethod(songInfoCanvasGO, "SetActive", &setInfoActive);
			il2cpp_utils::RunMethod(rightTrainingPosterPanelGO, "SetActive", &rightTrainingPoster);

			//Mock_UpdateSelectedSong(songSelectionUIController, self);
			UpdateSongInfoPanel(songSelectionUIController, level);
			EnableDifficultyIcons(level, songSelectionUIController);


			//il2cpp_utils::RunMethod(self, "SetSong");
			//TODO: Mock if needed

			Il2CppObject* gameManager;
			if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
				LOG("WARNING: Failed to get instance of GameManager\n");

			Difficulty difficulty = Difficulty::Easy;
			il2cpp_utils::GetFieldValue(&difficulty, gameManager, "difficulty");

			//TODO Move seeting songSwitch into Level
			Il2CppObject* levels = il2cpp_utils::GetFieldValue(gameManager, "levels");
			List<Il2CppObject*> levelDataDB(il2cpp_utils::GetFieldValue(levels, "levelData"));
			Il2CppObject* songSwitch = il2cpp_utils::GetFieldValue(levelDataDB[15], "songSwitch");
			il2cpp_utils::SetFieldValue(levelData, "songSwitch", songSwitch);

			Il2CppObject* map = level.GetGameMap(difficulty);

			il2cpp_utils::RunMethod(songSwitch, "SetValue");
			
			il2cpp_utils::RunMethod(gameManager, "SetLevelInternal", map);

			level.InsertSong();

			Il2CppObject* gameEvent = il2cpp_utils::GetFieldValue(self, "songSelectedEvent");
			il2cpp_utils::RunMethod(gameEvent, "Raise");

			database->SelectedCustomLevel(true);
		}
		else
		{
			database->SelectedCustomLevel(false);
			OnClickSong_orig(self); // We are not clicking on an custom level, just call stuff in ordinary fashion
		}
	}


	MAKE_HOOK(SelectedEasyDifficulty, void, Il2CppObject* self)
	{
		if (database->SelectedCustomLevel())
		{
			SetDifficulty(Difficulty::Easy);
		}
		else
		{
			SelectedEasyDifficulty_orig(self);
		}
	}

	MAKE_HOOK(SelectedNormalDifficulty, void, Il2CppObject* self)
	{
		if (database->SelectedCustomLevel())
		{
			SetDifficulty(Difficulty::Normal);
		}
		else
		{
			SelectedNormalDifficulty_orig(self);
		}
	}

	MAKE_HOOK(SelectedHardDifficulty, void, Il2CppObject* self)
	{
		if (database->SelectedCustomLevel())
		{
			SetDifficulty(Difficulty::Hard);
		}
		else
		{
			SelectedHardDifficulty_orig(self);
		}
	}

	MAKE_HOOK(SelectedExpertDifficulty, void, Il2CppObject* self)
	{
		if (database->SelectedCustomLevel())
		{
			SetDifficulty(Difficulty::Expert);
		}
		else
		{
			SelectedExpertDifficulty_orig(self);
		}
	}

	MAKE_HOOK(OnUpdatedPreviousHighScore, void, Il2CppObject* self)
	{
		if (database->SelectedCustomLevel())
		{
			LOG("SongInfoUI$$OnUpdatedPreviousHighScore: Figure out how we can update highscore\n");
		}
		else 
		{
			OnUpdatedPreviousHighScore_orig(self);
		}
	}


	MAKE_HOOK(Get_SourceClipName, Il2CppString*, Il2CppObject* self)
	{
		Il2CppString* str = Get_SourceClipName_orig(self);

		Il2CppObject* gameManager;
		if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
			LOG("WARNING: Failed to get instance of GameManager\n");
		bool playing = false;
		il2cpp_utils::GetFieldValue(&playing, gameManager, "playing");
		if (playing)
		{
			Il2CppString* str2, *str3;
			il2cpp_utils::GetFieldValue(&str2, il2cpp_utils::GetClassFromName("", "MusicManager"), "songName");
			Il2CppObject* player;
			il2cpp_utils::GetFieldValue(&player, il2cpp_utils::GetClassFromName("", "MusicManager"), "player");

			il2cpp_utils::RunMethod(&str3, player, "GetCurrentClipName");
			if (str != nullptr && str2 != nullptr && str3 != nullptr)
				LOG("\tGet_SourceClipName = %s\nMusicManager.songName = %s\nPlayer.GetCurrentClipName = %s\n\n",
					to_utf8(csstrtostr(str)).c_str(),
					to_utf8(csstrtostr(str2)).c_str(),
					to_utf8(csstrtostr(str3)).c_str()
				);
		}


		return str;
	}


	void initHooks(funchook_t* funchookp)
	{
		Start_orig = (Start_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "Start", 0)->methodPointer;
		INSTALL_HOOK(Start);

		OnClickSong_orig = (OnClickSong_t)il2cpp_utils::GetMethod("", "SongPanelUIController", "OnClick", 0)->methodPointer;
		INSTALL_HOOK(OnClickSong);

		OnUpdatedPreviousHighScore_orig = (OnUpdatedPreviousHighScore_t)il2cpp_utils::GetMethod("", "SongInfoUI", "OnUpdatedPreviousHighScore", 0)->methodPointer;
		INSTALL_HOOK(OnUpdatedPreviousHighScore);

		//Difficulty hooks
		SelectedEasyDifficulty_orig = (SelectedEasyDifficulty_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "SelectedEasyDifficulty", 0)->methodPointer;
		INSTALL_HOOK(SelectedEasyDifficulty);

		SelectedNormalDifficulty_orig = (SelectedNormalDifficulty_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "SelectedNormalDifficulty", 0)->methodPointer;
		INSTALL_HOOK(SelectedNormalDifficulty);

		SelectedHardDifficulty_orig = (SelectedHardDifficulty_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "SelectedHardDifficulty", 0)->methodPointer;
		INSTALL_HOOK(SelectedHardDifficulty);

		SelectedExpertDifficulty_orig = (SelectedExpertDifficulty_t)il2cpp_utils::GetMethod("", "SongSelectionUIController", "SelectedExpertDifficulty", 0)->methodPointer;
		INSTALL_HOOK(SelectedExpertDifficulty);



		//Get_SourceClipName_orig = (Get_SourceClipName_t)il2cpp_utils::GetMethod("SonicBloom.Koreo", "Koreography", "get_SourceClipName", 0)->methodPointer;
		//INSTALL_HOOK(Get_SourceClipName);
	}

};

