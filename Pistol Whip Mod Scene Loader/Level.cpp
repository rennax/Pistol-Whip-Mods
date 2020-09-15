#include "Level.hpp"
#include <fstream>
#include "Sprite.hpp"

Level::Level(fs::path levelPath) : path(levelPath)
{
}

Level::~Level()
{
}


bool Level::InsertSong()
{
	//TODO, at startup, check if the file is not renamed to its old name
	try
	{
		fs::path toCopy = path;
		toCopy.append("song.wem");
		fs::path destination(songPath);
		if (!fs::exists(fs::path(songPathBackup)))
		{
			if (!std::rename(songPath, songPathBackup))
			{
				LOG("Failed to rename Religion' wem file\n");
			}
		}

		fs::copy(toCopy, destination, fs::copy_options::overwrite_existing); // We have already made sure copy exists
	}
	catch (const std::exception& e)
	{
		LOG("%s\n", e.what());
		return false;
	}
	return true;
}

Il2CppObject* Level::GetLevelData()
{
	return levelData;
}

AlbumArtMetadata& Level::GetAlbumArt()
{
	return albumArt;
}

Il2CppString* Level::GetSongName()
{
	Il2CppString* name;
	il2cpp_utils::GetFieldValue(&name, levelData, "songName");
	return name;
}

void Level::Load()
{
	fs::path levelDataPath = path;
	json levelJson;
	std::ifstream i(levelDataPath.concat("/level.json"));
	i >> levelJson;
	i.close();

	levelData = level.Load(levelJson["levelData"]);
	albumArt.levelData = levelData;
	LoadAlbumArt(levelJson["albumArtMetadata"]);
}

void Level::LoadAlbumArt(json j)
{
	albumArt.artIsWIP = j["artIsWIP"];
	albumArt.songArtists = il2cpp_utils::createcsstr(j["songArtists"].get<std::string>());
	albumArt.tempo = j["tempo"];

	fs::path tempArtPath = path;
	tempArtPath /= j["art"].get<std::string>();
	Sprite sprite(tempArtPath, j["imgWidth"], j["imgHeight"]); // LoadImage should resize by itself
	albumArt.art = sprite.GetObj();
}

void Level::PartialLoad()
{
}
