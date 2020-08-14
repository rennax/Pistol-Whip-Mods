#include "LevelData.hpp"
#include "List.hpp"
#include "ColorShiftPoint.hpp"
#include "TrackSection.hpp"
#include "AssetBundle.hpp"
#include "WwiseKoreographySet.hpp"
#include "typedefs.h"
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

LevelData::LevelData(Il2CppObject* _gameManager) : gameManager(_gameManager)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "LevelData");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create LevelData object\n");
	else
		LOG("Created LevelData object\n");

	auto nameProp = il2cpp_utils::GetPropertySetMethod(klass, "name");
	Il2CppString* str = il2cpp_utils::createcsstr("Religion_Data");
	il2cpp_utils::RunMethod(self, nameProp, str);
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

Il2CppObject* LevelData::Load(json level)
{
	LoadSongSwitch(level["song"]);
	LoadGameMaps(level["gameMaps"]);
	LoadAndSetWwiseKoreographySets(level["koreoSets"]);
	LoadTrackSections(level["sections"]);
	LoadColorShiftPoints(level["colors"]);
	LoadWorldRegions(level["regions"]);


	songLength = level["songLength"];
	if (!il2cpp_utils::SetFieldValue(self, "songLength", &songLength))
		LOG("WARNING: Failed to assign songLength in levelData\n");
	
	songName = level["songName"];
	Il2CppString* name = il2cpp_utils::createcsstr(songName.c_str());
	if (!il2cpp_utils::SetFieldValue(self, "songName", name))
		LOG("WARNING: Failed to assign songName in LevelData\n");
	

	return self;
}

void LevelData::LoadSongSwitch(json j)
{

	LOG("TODO Switch song in LevelData::LoadSongSwitch\n");
	//TODO, at startup, check if the file is not renamed to its old name
	/*
	* Rename current lastReleasedScene to have postfix _saved
	* Get location of current selected custom song
	* Copy over the .wem file and rename it to have the id of lastReleasedScene
	* Done
	*/
	try
	{
		fs::path toCopy("Custom Levels/x02/song.wem");
		fs::path destination(lastReleasedScene);
		if (!fs::exists(fs::path(lastReleasedSceneRenamed)))
		{
			if (!std::rename(lastReleasedScene, lastReleasedSceneRenamed))
			{
				LOG("Failed to rename Religion' wem file\n");
			}
		}
		
		fs::copy(toCopy, destination, fs::copy_options::overwrite_existing); // We have already made sure copy exists
	}
	catch (const std::exception& e)
	{
		LOG("%s\n", e.what());
	}

}

void LevelData::LoadGameMaps(json j)
{
	for (auto& gm : j) {
		GameMap* map = new GameMap(self);
		map->Load(gm);



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
		array_maps = il2cpp_functions::array_new(klass, maps.size());

	}


	for (size_t i = 0; i < maps.size(); i++)
	{
		il2cpp_array_set(array_maps, Il2CppObject*, i, maps[i]->GetIl2CppObject());
	}

	if (!il2cpp_utils::SetFieldValue(self, "maps", array_maps))
		LOG("WARNING: Failed to set new maps array in LevelData\n");
}

void LevelData::LoadTrackSections(json j)
{
	//////FOR TEST
	//List<Il2CppObject*> trackSections(il2cpp_utils::GetFieldValue(self, "sections"));
	////trackSections.Clear();
	//auto klass = il2cpp_utils::GetClassFromName("", "TrackSection");
	//Il2CppObject* section = nullptr;
	//int type = 0;
	//il2cpp_utils::RunMethod(&section, klass, "Create", &type);
	//trackSections.Add(section);
	//TrackSection sec(section);
	//j = sec.Dump();
	//std::ofstream o = std::ofstream("TrackSection_ctor.json");
	//o << std::setw(4) << j << std::endl;
	//o.close();
	List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(self, "sections"));
	for (auto& sec : j)
	{
		TrackSection section;
		sections.Add(section.Load(sec));
	}
}

void LevelData::LoadWorldRegions(json j)
{
	List<Il2CppObject*> regions(il2cpp_utils::GetFieldValue(self, "colors"));
	for (auto& r : j)
	{
		//TODO move into own class
		Il2CppObject* region = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "WorldRegion"));
		il2cpp_utils::RunMethod(region, ".ctor");

		int32_t type = r["type"];
		Vector3i position = r["position"];
		Vector3i min = r["min"];
		Vector3i max = r["max"];
		
		il2cpp_utils::SetFieldValue(region, "position", &position);
		il2cpp_utils::SetFieldValue(region, "min", &min);
		il2cpp_utils::SetFieldValue(region, "max", &max);
		il2cpp_utils::SetFieldValue(region, "type", &type);

		regions.Add(region);
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


	//for (size_t i = 0; i < maps.size(); i++)
	//{
	//	Il2CppObject* trackData = il2cpp_utils::GetFieldValue(maps[i]->GetIl2CppObject(), "trackData");
	//	Il2CppObject* koreo = il2cpp_utils::GetFieldValue(trackData, "koreography");
	//	List<Il2CppObject*>koreographies(il2cpp_utils::GetFieldValue(koreoSets->values[i], "koreographies"));
	//	uint32_t id = j.at(i)["koreographies"].at(0)["mediaID"];
	//	il2cpp_utils::SetFieldValue(koreographies[i], "mediaID", &id);
	//	il2cpp_utils::SetFieldValue(koreographies[i], "koreo", koreo);
	//}
}
