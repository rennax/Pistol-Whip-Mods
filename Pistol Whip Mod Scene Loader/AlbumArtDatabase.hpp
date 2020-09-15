#ifndef ALBUMARTDATABASE_HPP
#define ALBUMARTDATABASE_HPP
#include "json.hpp"
#include "il2cpp_utils.hpp"

struct AlbumArtMetadata {
	Il2CppObject* levelData; //LevelData
	Il2CppString* songArtists;
	int32_t tempo;
	Il2CppObject* art; //Sprite
	bool artIsWIP;
};

class AlbumArtDatabase
{
public:
	AlbumArtDatabase(Il2CppObject* database); // We must grap the database from an already existing database
	~AlbumArtDatabase();
	void AddEntry(Il2CppObject* levelData, AlbumArtMetadata& albumArt);
private:
	Il2CppObject* self; // AlbumArtDatabase
	Il2CppObject* albumMetadataDict; // Dictionary<LevelData, AlbumArtDatabase.AlbumArtMetadata>
};


#endif // !ALBUMARTDATABASE_HPP
