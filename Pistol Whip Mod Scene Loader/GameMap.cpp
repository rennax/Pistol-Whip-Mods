#include "GameMap.hpp"


GameMap::GameMap()
{
	LOG("WARNING: Initizalized GameMap without any LevelData field.\n");
}

GameMap::GameMap(Il2CppObject* levelData_, Il2CppObject* gameMap)
{
	levelData = levelData_;
	self = gameMap;
}

GameMap::GameMap(Il2CppObject* levelData_)
{
	levelData = levelData_;
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GameMap");
	self = il2cpp_functions::object_new(klass);
}

GameMap::~GameMap()
{
}

Il2CppObject* GameMap::Load(json j)
{
	geoSet = new GeoSet::GeoSet();
	Il2CppObject* geo = geoSet->Load(j["geoset"]);

	il2cpp_utils::RunMethod(self, ".ctor", geo);

	//TODO load trackData
	trackData = new TrackData(levelData);
	Il2CppObject* track = trackData->Load(j["trackData"]);

	if (!il2cpp_utils::SetFieldValue(self, "trackData", track))
		LOG("WARNING: Failed to assign TrackData field in GameMap\n");

	if (!il2cpp_utils::SetFieldValue(self, "isPlayable", &isPlayable))
		LOG("WARNING: Failed to assign isPlayable in GameMap\n");


	if (!il2cpp_utils::SetFieldValue(self, "data", levelData))
		LOG("WARNING: Failed to assign LevelData field in GameMap\n");
	return self;
}

Il2CppObject* GameMap::GetIl2CppObject()
{
	return self;
}
