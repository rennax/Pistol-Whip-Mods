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
	Level GetLevelAtLevelIndex(uint32_t levelIndex);
	uint32_t HighestLevelIndex();
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
};


#endif // !CUSTOMLEVELDATABASE_HPP
