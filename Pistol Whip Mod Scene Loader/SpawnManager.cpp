#include "SpawnManager.hpp"
#include "utils.h"

SpawnManager::SpawnManager()
{
}

SpawnManager::~SpawnManager()
{
}

MAKE_HOOK(OnSongTimeSet, void, Il2CppObject* self, Il2CppObject* songTimeEvent) {
	LOG("SpawnManager::OnSongTimeSet()\n");
	OnSongTimeSet_orig(self, songTimeEvent);
}

MAKE_HOOK(OnSongStart, void, Il2CppObject* self) {
	LOG("SpawnManager::OnSongStart()\n");
	OnSongStart_orig(self);
	if (il2cpp_utils::GetFieldValue(self, "data") == nullptr)
		LOG("\tTrackData is null\n");
}

MAKE_HOOK(QueueSpawns, void, Il2CppObject* self) {
	LOG("SpawnManager::QueueSpawns()\n");
	Il2CppObject* trackData = il2cpp_utils::GetFieldValue(self, "data");
	if (trackData == nullptr)
	{
		LOG("SpawnManager::QueueSpawns(), the trackData is null\n");
	}

	QueueSpawns_orig(self);
}

MAKE_HOOK(PrespawnEnemies, void, Il2CppObject* self) {
	LOG("SpawnManager::PrespawnEnemies()\n");
	PrespawnEnemies_orig(self);
}


MAKE_HOOK(OnSongSeek, void, Il2CppObject* self) {
	LOG("SpawnManager::OnSongSeek()\n");
	OnSongSeek_orig(self);
}

MAKE_HOOK(PlaySong, void, Il2CppObject* koreoSet, Il2CppObject* song, float seekTime) {
	LOG("MusicManager::PlaySong()\n");
	PlaySong_orig(koreoSet, song, seekTime);
}

MAKE_HOOK(get_difficulty, int32_t, Il2CppObject* self) {
	LOG("GameMap.get_difficulty()\n");
	return get_difficulty_orig(self);
}

void SpawnManager::initHooks(funchook_t* funchookp)
{
	OnSongTimeSet_orig = (OnSongTimeSet_t)il2cpp_utils::GetMethod("", "SpawnManager", "OnSongTimeSet", 1)->methodPointer;
	INSTALL_HOOK(OnSongTimeSet);

	OnSongStart_orig = (OnSongStart_t)il2cpp_utils::GetMethod("", "SpawnManager", "OnSongStart", 0)->methodPointer;
	INSTALL_HOOK(OnSongStart);

	OnSongSeek_orig = (OnSongSeek_t)il2cpp_utils::GetMethod("", "SpawnManager", "OnSongSeek", 0)->methodPointer;
	INSTALL_HOOK(OnSongSeek);

	QueueSpawns_orig = (QueueSpawns_t)il2cpp_utils::GetMethod("", "SpawnManager", "QueueSpawns", 0)->methodPointer;
	INSTALL_HOOK(QueueSpawns);

	PrespawnEnemies_orig = (PrespawnEnemies_t)il2cpp_utils::GetMethod("", "SpawnManager", "PrespawnEnemies", 0)->methodPointer;
	INSTALL_HOOK(PrespawnEnemies);


	//PlaySong_orig = (PlaySong_t)il2cpp_utils::GetMethod("", "MusicManager", "PlaySong", 3)->methodPointer;
	//INSTALL_HOOK(PlaySong);

	/*get_difficulty_orig = (get_difficulty_t)il2cpp_utils::GetMethod("", "GameMap", "get_difficulty", 0)->methodPointer;
	INSTALL_HOOK(get_difficulty);*/

}
