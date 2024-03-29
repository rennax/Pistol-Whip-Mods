#include "LevelData.hpp"
#include "List.hpp"
#include "ColorShiftPoint.hpp"
#include "TrackSection.hpp"
#include "AssetBundle.hpp"
#include "WwiseKoreographySet.hpp"
#include "typedefs.h"
#include "WorldVolume.hpp"
#include <filesystem>
#include <cstdio>

using namespace CSharp;
namespace fs = std::filesystem;

MAKE_HOOK(get_isPlayable, bool, void* self) {
	LOG("LevelData::get_isPlayable is called\n");
	return true;
}

void LevelData::initHooks(funchook_t* funchookp)
{
	LOG("LevelData::initHooks()\n");
	get_isPlayable_orig = (get_isPlayable_t)il2cpp_utils::GetMethod("", "LevelData", "get_isPlayable", 0)->methodPointer;
	INSTALL_HOOK(get_isPlayable);
}

LevelData::LevelData(Il2CppObject* _gameManager, Il2CppObject* obj) : self(obj), gameManager(_gameManager)
{
}

LevelData::LevelData()
{


	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "LevelData");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create LevelData object\n");
	else
		LOG("Created LevelData object\n");


	if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
		LOG("WARNING: Failed to get instance of GameManager\n");

}

LevelData::~LevelData()
{
}

json LevelData::Dump()
{
	json j;


	List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(self, "sections"));
	j["sections"] = {};
	LOG("LevelData: length of sections = %u\n", sections.Count());
	for (size_t i = 0; i < sections.Count(); i++)
	{
		TrackSection section(sections[i]);
		j["sections"].push_back(section.Dump());
	}

	List<Il2CppObject*> regions(il2cpp_utils::GetFieldValue(self, "regions"));
	LOG("LevelData: length of regions = %u\n", regions.Count());
	for (size_t i = 0; i < regions.Count(); i++)
	{
		//...
	}
	
	List<Il2CppObject*> colors(il2cpp_utils::GetFieldValue(self, "colors"));
	LOG("LevelData: length of colors = %u\n", colors.Count());
	for (size_t i = 0; i < colors.Count(); i++)
	{
		ColorShiftPoint color(colors[i]);
		j["colors"].push_back(color.Dump());

	}

	List<Il2CppObject*> worldObjects(il2cpp_utils::GetFieldValue(self, "worldObjects"));
	LOG("LevelData: length of worldObjects = %u\n", worldObjects.Count());
	for (size_t i = 0; i < worldObjects.Count(); i++)
	{
		//...
	}

	List<Il2CppObject*> simpleStaticWorldObjects(il2cpp_utils::GetFieldValue(self, "simpleStaticWorldObjects"));
	LOG("LevelData: length of simpleStaticWorldObjects = %u\n", simpleStaticWorldObjects.Count());
	for (size_t i = 0; i < simpleStaticWorldObjects.Count(); i++)
	{
		//...
	}

	List<Il2CppObject*> simpleDynamicWorldObjects(il2cpp_utils::GetFieldValue(self, "simpleDynamicWorldObjects"));
	LOG("LevelData: length of simpleDynamicWorldObjects = %u\n", simpleDynamicWorldObjects.Count());
	for (size_t i = 0; i < simpleDynamicWorldObjects.Count(); i++)
	{
		//...
	}

	List<Il2CppObject*> staticCullingRanges(il2cpp_utils::GetFieldValue(self, "staticCullingRanges"));
	LOG("LevelData: length of staticCullingRanges = %u\n", staticCullingRanges.Count());
	for (size_t i = 0; i < staticCullingRanges.Count(); i++)
	{
		//...
	}

	List<Il2CppObject*> dynamicCullingRanges(il2cpp_utils::GetFieldValue(self, "dynamicCullingRanges"));
	LOG("LevelData: length of dynamicCullingRanges = %u\n", dynamicCullingRanges.Count());
	for (size_t i = 0; i < dynamicCullingRanges.Count(); i++)
	{
		//...
	}

	bool skipIndexing = false;
	il2cpp_utils::GetFieldValue(&skipIndexing, self, "skipIndexing");
	j["skipIndexing"] = skipIndexing;

	int levelIndex = -1;
	il2cpp_utils::GetFieldValue(&levelIndex, self, "levelIndex");
	j["levelIndex"] = levelIndex;
	
	Il2CppString* songName = nullptr;
	il2cpp_utils::GetFieldValue(&songName, self, "songName");
	j["songName"] = csstrtostr(songName);
	
	float songLength;
	il2cpp_utils::GetFieldValue(&songLength, self, "songLength");
	j["songLength"] = songLength;

	return j;
}

Il2CppObject* LevelData::Load(json level, fs::path path)
{
	pathToLevelDir = path;

	LoadGameMaps(level["gameMaps"]);
	LoadAndSetWwiseKoreographySets(level["koreoSets"]);
	LoadTrackSections(level["sections"]);
	LoadColorShiftPoints(level["colors"]);
	LoadWorldVolumes(level["volumes"]);


	songLength = level["songLength"];
	if (!il2cpp_utils::SetFieldValue(self, "songLength", &songLength))
		LOG("WARNING: Failed to assign songLength in levelData\n");
	
	songName = level["songName"];
	if (!il2cpp_utils::SetFieldValue(self, "songName", il2cpp_utils::createcsstr(songName.c_str())))
		LOG("WARNING: Failed to assign songName in LevelData\n");

	static auto nameProp = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("", "LevelData"), "name");
	std::string name = "LevelData_" + songName;
	il2cpp_utils::RunMethod(self, nameProp, il2cpp_utils::createcsstr(name));

	
	description = level["description"];
	if (!il2cpp_utils::SetFieldValue(self, "songName", il2cpp_utils::createcsstr(description.c_str())))
		LOG("WARNING: Failed to assign songName in LevelData\n");

	return self;
}

std::vector<Difficulty> LevelData::GetDifficulties()
{
	return difficulties;
}

void LevelData::LoadSongSwitch(json j)
{

	LOG("LevelData::LongSongSwitch() is depricated. If this function is called, then something is wrong\n");
	////TODO, at startup, check if the file is not renamed to its old name
	///*
	//* Rename current lastReleasedScene to have postfix _saved
	//* Get location of current selected custom song
	//* Copy over the .wem file and rename it to have the id of lastReleasedScene
	//* Done
	//*/
	//try
	//{
	//	fs::path toCopy("Custom Levels/x02/song.wem");
	//	fs::path destination(lastReleasedScene);
	//	if (!fs::exists(fs::path(lastReleasedSceneRenamed)))
	//	{
	//		if (!std::rename(lastReleasedScene, lastReleasedSceneRenamed))
	//		{
	//			LOG("Failed to rename Religion' wem file\n");
	//		}
	//	}
	//	
	//	fs::copy(toCopy, destination, fs::copy_options::overwrite_existing); // We have already made sure copy exists
	//}
	//catch (const std::exception& e)
	//{
	//	LOG("%s\n", e.what());
	//}

}

void LevelData::LoadGameMaps(json j)
{
	difficulties.clear();

	for (auto& gm : j) {
		GameMap* map = new GameMap(self);
		map->Load(gm, pathToLevelDir);
		difficulties.push_back(gm["trackData"]["difficulty"].get<Difficulty>());
		maps.push_back(map);
	}

	Il2CppArray* array_maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(self, "maps"));

	//We might create a memory leak here.
	//TODO check and fix
	if (array_maps == nullptr ||
		il2cpp_functions::array_length(array_maps) < maps.size())
	{
		//il2cpp_functions::free(array_maps);
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GameMap");
		//NOTE As of 8/31/2020 there must be 3 GameMaps no matter what
		//TODO Test if this is actually the case
		array_maps = il2cpp_functions::array_new(klass, 3);

	}

	//NOTE As of 8/31/2020 there must be 3 GameMaps no matter what
	//TODO fix in cases where there are multiple gamemaps in actual file
	for (size_t i = 0; i < j.size(); i++)
	{
		il2cpp_array_set(array_maps, Il2CppObject*, i, maps[0]->GetIl2CppObject());
	}

	if (!il2cpp_utils::SetFieldValue(self, "maps", array_maps))
		LOG("WARNING: Failed to set new maps array in LevelData\n");
}

void LevelData::LoadTrackSections(json j)
{
	List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(self, "sections"));
	for (auto& sec : j)
	{
		TrackSection section;
		sections.Add(section.Load(sec));
	}
}

void LevelData::LoadWorldVolumes(json j)
{
	List<Il2CppObject*> worldVolumes(il2cpp_utils::GetFieldValue(self, "volumes"));
	for (auto& v : j)
	{
		WorldVolume volume;

		worldVolumes.Add(volume.Load(v));
	}
}

void LevelData::LoadColorShiftPoints(json j)
{
	List<Il2CppObject*> colors(il2cpp_utils::GetFieldValue(self, "colors"));
	for (auto& p : j)
	{
		ColorShiftPoint point;
		colors.Add(point.Load(p));
	}
}


void LevelData::LoadWorldObjects(json j)
{
	auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "GameObject");
	auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

	for (auto& wo : j)
	{
		json p = wo["point"]["position"];
		json r = wo["point"]["rotation"];
		json s = wo["scale"];

		WorldPoint point = {
			{p["x"], p["y"], p["z"]},
			{r["x"], r["y"], r["z"], r["w"]}
		};
		Vector3 scale = {
			s["x"],
			s["y"],
			s["z"]
		};

		Il2CppObject* bundle = AssetBundle::LoadFromFile("Custom Levels/x02/static_objects");
		Il2CppObject* prefab = AssetBundle::LoadAsset(bundle, wo["prefabName"], type);
		if (prefab == nullptr)
		{
			LOG("ERROR: GeoSet::loadStaticProps: Prefab %s doesn't exist\n", wo["prefabName"]);
		}

		WorldObject worldObject(point, prefab, scale);

		worldObjects.push_back(worldObject);
	}

	List<Il2CppObject*> worldObjectsList(il2cpp_utils::GetFieldValue(self, "worldObjects"));
	for (auto& wo : worldObjects)
	{
		worldObjectsList.Add(wo.GetObj());
	}
}

void LevelData::LoadSimpleStaticWorldObjects(json j)
{
}

void LevelData::LoadSimpleDynamicWorldObjects(json j)
{
}

void LevelData::LoadStaticCullingRanges(json j)
{
}

void LevelData::LoadDynamicCullingRanges(json j)
{
}

void LevelData::LoadAndSetWwiseKoreographySets(json j)
{
	//Set LevelDatabase.koreoSets as this is used when fetching the song
	Il2CppObject* levelDB = il2cpp_utils::GetFieldValue(gameManager, "levels"); //LevelDatabase
	Array<Il2CppObject*>* koreoSets;
	il2cpp_utils::GetFieldValue(&koreoSets, levelDB, "koreoSets");
	List<Il2CppObject*> koreographiesEasy(il2cpp_utils::GetFieldValue(koreoSets->values[0], "koreographies"));
	Il2CppObject* koreo = nullptr;
	for (size_t i = 0; i < koreographiesEasy.Count(); i++)
	{
		uint32_t id;
		il2cpp_utils::GetFieldValue(&id, koreographiesEasy[i], "mediaID");
		if (id == 561074166)
		{
			koreo = koreographiesEasy[i];
			break;
		}
	}

	if (koreo != nullptr)
	{
		Il2CppObject* trackData = il2cpp_utils::GetFieldValue(maps[0]->GetIl2CppObject(), "trackData");
		Il2CppObject* koreography = il2cpp_utils::GetFieldValue(trackData, "koreography");
		il2cpp_utils::SetFieldValue(koreo, "koreo", koreography);
		
		Il2CppString* str;
		il2cpp_utils::GetFieldValue(&str, koreography, "clipName");
		LOG("Set new koreography: %s\n\n", to_utf8(csstrtostr(str)).c_str());
	}
}
