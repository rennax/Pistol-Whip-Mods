#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "il2cpp_utils.hpp"
#include <string>
#include <filesystem>
#include "json.hpp"
#include "LevelData.hpp"
#include "AlbumArtDatabase.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;



class Level
{
public:
	Level(fs::path levelPath);
	~Level();
	//Il2CppObject* LoadLevel();
	bool InsertSong();
	Il2CppObject* GetLevelData();
	AlbumArtMetadata& GetAlbumArt();
	Il2CppString* GetSongName();
	void Load();
private:
	void LoadAlbumArt(json j);
	void PartialLoad();
private:
	fs::path path;
	AlbumArtMetadata albumArt;

	LevelData level;
	Il2CppObject* levelData;

	const char* songPath = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166.wem";
	const char* songPathBackup = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166_backup.wem";

};


#endif // !LEVEL_HPP
