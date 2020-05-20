#include "LevelData.hpp"
#include "List.hpp"
#include "ColorShiftPoint.hpp"

#include "AssetBundle.hpp"

using namespace CSharp;

LevelData::LevelData(Il2CppObject* obj)
{
	self = obj;
}

LevelData::LevelData()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "LevelData");
	self = il2cpp_functions::object_new(klass);

	const MethodInfo* ctor = il2cpp_utils::GetMethod(klass, ".ctor", 0);
	il2cpp_utils::RunMethod(self, ctor);
	LOG("Created LevelData object\n");
}

LevelData::~LevelData()
{
}

json LevelData::Dump()
{
	json j;


	List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(self, "sections"));
	LOG("LevelData: length of sections = %u\n", sections.Count());
	for (size_t i = 0; i < sections.Count(); i++)
	{
		//...
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

	//Il2CppArray* sectionData;


	return j;
}

Il2CppObject* LevelData::Load(json level)
{

	LoadWorldObjects(level["worldObjects"]);

	//loadDynamicProps(geo["dynamicProps"]);



	List<Il2CppObject*> worldObjectsList(il2cpp_utils::GetFieldValue(self, "worldObjects"));
	for (auto& wo : worldObjects)
	{
		worldObjectsList.Add(wo.GetObj());
	}
	return self;
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
}
