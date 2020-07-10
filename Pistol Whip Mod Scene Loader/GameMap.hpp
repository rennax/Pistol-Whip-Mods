#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "WorldObject.hpp"
#include "GeoSet.hpp"
#include "TrackData.hpp"

using json = nlohmann::json;

class GameMap
{
public:
	GameMap();
	GameMap(Il2CppObject* levelData_, Il2CppObject* gameMap);
	GameMap(Il2CppObject* levelData_);
	~GameMap();
	Il2CppObject* Load(json j);
	Il2CppObject* GetIl2CppObject(); // Can be called after load has been called
private:
	Il2CppObject* self;
	Il2CppObject* levelData;
	GeoSet::GeoSet* geoSet;
	TrackData* trackData;
	bool isPlayable = true;
};


#endif // !GAMEMAP_HPP
