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

	Il2CppString* str;
	il2cpp_utils::RunMethod(&str, self, "get_name");
	LOG("GameMap.get_name %s\n", to_utf8(csstrtostr(str)).c_str());

	bool isPlayable = j["isPlayable"];
	il2cpp_utils::SetFieldValue(self, "isPlayable", &isPlayable);
	
	int32_t enemyCount = j["enemyCount"];
	il2cpp_utils::SetFieldValue(self, "enemyCount", &enemyCount);

	int32_t enemyIgnoreCount = j["enemyIgnoreCount"];
	il2cpp_utils::SetFieldValue(self, "enemyIgnoreCount", &enemyIgnoreCount);

	int32_t enemyHitIgnoreCount = j["enemyHitIgnoreCount"];
	il2cpp_utils::SetFieldValue(self, "enemyHitIgnoreCount", &enemyHitIgnoreCount);

	int32_t rankedEnemyCount = j["rankedEnemyCount"];
	il2cpp_utils::SetFieldValue(self, "rankedEnemyCount", &rankedEnemyCount);

	int32_t trueMaxScore = j["trueMaxScore"];
	il2cpp_utils::SetFieldValue(self, "trueMaxScore", &trueMaxScore);

	int32_t rankMaxScore = j["rankMaxScore"];
	il2cpp_utils::SetFieldValue(self, "rankMaxScore", &rankMaxScore);

	int32_t hitCount = j["hitCount"];
	il2cpp_utils::SetFieldValue(self, "hitCount", &hitCount);

	int32_t rankedHitCount = j["rankedHitCount"];
	il2cpp_utils::SetFieldValue(self, "rankedHitCount", &rankedHitCount);


	return self;
}

Il2CppObject* GameMap::GetIl2CppObject()
{
	return self;
}
