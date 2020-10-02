#ifndef CUSTOMLEVELDATABASE_HPP
#define CUSTOMLEVELDATABASE_HPP
#include <string>
#include "Level.hpp"
#include "il2cpp_utils.hpp"
#include "AlbumArtDatabase.hpp"

class CustomLevelDatabase
{
public:
	CustomLevelDatabase(Il2CppObject* controller);
	~CustomLevelDatabase();
	Level& GetLevelAtLevelIndex(uint32_t levelIndex);
	void CurrentIndex(uint32_t index);
	uint32_t CurrentIndex();
	uint32_t HighestLevelIndex();
	void SelectedCustomLevel(bool isCustom);
	bool SelectedCustomLevel();
private:
	void BuildDatabase();
	void PopulateSongSelectionUI();
	void CreatePageIndicators(uint32_t count);
	void CreateSongPanel();
private:
	Il2CppObject* songSelectionUIController;

	std::vector<Level> levels;
	const std::string customLevelPath = "Custom Levels";
	AlbumArtDatabase albumArtDB;

	uint32_t highestLevelIndex;
	const int32_t songsPerPage = 4;

	uint32_t currentIndex = 1;
	bool selectedCustomLevel = false;
};


#endif // !CUSTOMLEVELDATABASE_HPP
