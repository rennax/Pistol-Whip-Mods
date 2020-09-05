#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "il2cpp_utils.hpp"
#include <string>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;

struct AlbumArtMetadata {
	Il2CppObject* levelData; //LevelData
	std::string songArtists;
	int32_t tempo;
	Il2CppObject* art; //Sprite
	bool artIsWIP;
};

class Level
{
public:
	Level(fs::path levelPath);
	~Level();
	Il2CppObject* LoadLevel();
	bool LoadSong();
private:
	void LoadAlbumArt();
private:
	fs::path path;
	AlbumArtMetadata albumArt;
	json level;

	Il2CppObject* albumArtDB;
};


#endif // !LEVEL_HPP
