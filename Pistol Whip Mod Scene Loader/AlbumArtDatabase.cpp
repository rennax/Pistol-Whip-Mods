#include "AlbumArtDatabase.hpp"

AlbumArtDatabase::AlbumArtDatabase(Il2CppObject* database) : self(database)
{
	il2cpp_utils::GetFieldValue(&albumMetadataDict, self, "albumMetadataDict");
}

AlbumArtDatabase::~AlbumArtDatabase()
{
}

void AlbumArtDatabase::AddEntry(Il2CppObject* levelData, AlbumArtMetadata& albumArt)
{
	il2cpp_utils::RunMethod(albumMetadataDict, "Add", levelData, &albumArt);
}
