#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "WorldObject.hpp"
#include "GameMap.hpp"
#include <vector>

extern "C" { // name mangle 
#include <funchook.h>
}




using json = nlohmann::json;


class LevelData
{
public:
	static void initHooks(funchook_t* funchookp);
	LevelData(Il2CppObject* _gameManager, Il2CppObject* obj);
	LevelData(Il2CppObject* _gameManager);
	~LevelData();
	json Dump();
	Il2CppObject* Load(json j);
private:
	void LoadSongSwitch(json j); // TODO
	void LoadGameMaps(json j);
	void LoadTrackSections(json j); // TODO
	void LoadWorldRegions(json j);
	void LoadColorShiftPoints(json j);
	void LoadWorldObjects(json j);
	void LoadSimpleStaticWorldObjects(json j); // TODO
	void LoadSimpleDynamicWorldObjects(json j); // TODO
	void LoadStaticCullingRanges(json j); // TODO
	void LoadDynamicCullingRanges(json j); // TODO
	void LoadAndSetWwiseKoreographySets(json j);
private:
	Il2CppObject* gameManager; //Dont wanna deal with generic objects to get_instance
	std::vector<WorldObject> worldObjects;
	float songLength = 0;
	std::string songName;
	std::string songPath = "Custom Levels/x02/";
	const char* lastReleasedScene = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166.wem";
	const char* lastReleasedSceneRenamed = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166_backup.wem";
	Il2CppObject* self;
	std::vector<GameMap*> maps;
};

#endif // !LEVELDATA_HPP
