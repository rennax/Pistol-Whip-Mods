#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "WorldObject.hpp"
#include "GameMap.hpp"
#include <vector>

using json = nlohmann::json;


class LevelData
{
public:
	LevelData(Il2CppObject* obj);
	LevelData();
	~LevelData();
	json Dump();
	Il2CppObject* Load(json j);
private:
	void LoadSongSwitch(json j); // TODO
	void LoadGameMaps(json j); // TODO
	void LoadTrackSections(json j); // TODO
	void LoadWorldRegions(json j); // TODO;
	void LoadColorShiftPoints(json j); // TODO
	void LoadWorldObjects(json j);
	void LoadSimpleStaticWorldObjects(json j); // TODO
	void LoadSimpleDynamicWorldObjects(json j); // TODO
	void LoadStaticCullingRanges(json j); // TODO
	void LoadDynamicCullingRanges(json j); // TODO
private:
	std::vector<WorldObject> worldObjects;
	Il2CppObject* self;
	std::vector<GameMap*> maps;
};

#endif // !LEVELDATA_HPP
