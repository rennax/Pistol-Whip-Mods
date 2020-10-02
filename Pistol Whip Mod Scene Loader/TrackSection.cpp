#include "TrackSection.hpp"
#include "List.hpp"
#include "WorldObject.hpp"

using namespace CSharp;

TrackSection::TrackSection()
{
}

TrackSection::TrackSection(Il2CppObject* obj) : self(obj)
{
}


TrackSection::~TrackSection()
{
}

Il2CppObject* TrackSection::Load(json j)
{
	//Load data specific to the type deriving from TrackSection
	Section sectionType = static_cast<Section>(j["section"].get<int32_t>());
	auto klass = il2cpp_utils::GetClassFromName("", "TrackSection");
	il2cpp_utils::RunMethod(&self, klass, "Create", &sectionType);

	switch (sectionType)
	{
	case Section::Filled:
		LoadFilledSection(j);
		break;
	default:
		break;
	}
	
	Color color = j["color"];
	il2cpp_utils::RunMethod(self, "set_mainColor", &color);

	Color fogColor = j["fog"];
	il2cpp_utils::RunMethod(self, "set_fogColor", &fogColor);


	Color glowColor = j["glow"];
	il2cpp_utils::RunMethod(self, "set_glowColor", &glowColor);


	Color enemyColor = j["enemy"];
	il2cpp_utils::RunMethod(self, "set_enemyColor", &enemyColor);

	_customColors = j["_customColors"];
	il2cpp_utils::SetFieldValue(self, "_customColors", &_customColors);
	_customEnemyColor = j["_customEnemyColor"];
	il2cpp_utils::SetFieldValue(self, "_customEnemyColor", &_customEnemyColor);
	startingWall = j["startingWall"];
	il2cpp_utils::SetFieldValue(self, "startingWall", &startingWall);
	endingWall = j["endingWall"];
	il2cpp_utils::SetFieldValue(self, "endingWall", &endingWall);
	height = j["height"];
	il2cpp_utils::SetFieldValue(self, "height", &height);
	groundHeight = j["groundHeight"];
	il2cpp_utils::SetFieldValue(self, "groundHeight", &groundHeight);
	//seed = j["seed"];
	//il2cpp_utils::SetFieldValue(self, "seed", &seed);
	start = j["start"];
	il2cpp_utils::SetFieldValue(self, "start", &start);
	end = j["end"];
	il2cpp_utils::SetFieldValue(self, "end", &end);
	min = j["min"];
	il2cpp_utils::SetFieldValue(self, "min", &min);
	max = j["max"];
	il2cpp_utils::SetFieldValue(self, "max", &max);
	extent = j["extent"];
	il2cpp_utils::SetFieldValue(self, "extent", &extent);
	generateDebris = j["generateDebris"];
	il2cpp_utils::SetFieldValue(self, "generateDebris", &generateDebris);
	if (!j["debris"].is_null())
	{
		debris = j["debris"];
		il2cpp_utils::SetFieldValue(self, "debris", &debris);
	}
	//propSeed = j["propSeed"];
	//il2cpp_utils::SetFieldValue(self, "propSeed", &propSeed);
	yStep = j["yStep"];
	il2cpp_utils::SetFieldValue(self, "yStep", &yStep);
	zStep = j["zStep"];
	il2cpp_utils::SetFieldValue(self, "zStep", &zStep);

	int i = 0;

	yOffsets = reinterpret_cast<Array<int32_t>*>(il2cpp_functions::array_new(il2cpp_utils::GetClassFromName("System", "Int32"), j["yOffsets"].size()));
	for (auto it = j["yOffsets"].begin(); it != j["yOffsets"].end(); ++it)
	{
		yOffsets->values[i] = it.value();
		i++;
	}
	il2cpp_utils::SetFieldValue(self, "yOffsets", yOffsets);

	i = 0;
	zOffsets = reinterpret_cast<Array<int32_t>*>(il2cpp_functions::array_new(il2cpp_utils::GetClassFromName("System", "Int32"), j["zOffsets"].size()));
	for (auto it = j["zOffsets"].begin(); it != j["zOffsets"].end(); ++it)
	{
		zOffsets->values[i] = it.value();
		i++;
	}
	il2cpp_utils::SetFieldValue(self, "zOffsets", zOffsets);

	size = j["size"];
	il2cpp_utils::SetFieldValue(self, "size", &size);
	lastDebrisPoint = j["lastDebrisPoint"];
	il2cpp_utils::SetFieldValue(self, "lastDebrisPoint", &lastDebrisPoint);


	return self;
}

json TrackSection::Dump()
{
	Il2CppClass* klass = il2cpp_functions::object_get_class(self);
	LOG("TrackSection is class %s\n",il2cpp_functions::class_get_name(klass));
	
	//Fuck me
	il2cpp_utils::GetFieldValue(&colorHue, self, "colorHue");
	il2cpp_utils::GetFieldValue(&colorSaturation, self, "colorSaturation");
	il2cpp_utils::GetFieldValue(&colorValue, self, "colorValue");
	il2cpp_utils::GetFieldValue(&fogHue, self, "fogHue");
	il2cpp_utils::GetFieldValue(&fogSaturation, self, "fogSaturation");
	il2cpp_utils::GetFieldValue(&fogValue, self, "fogValue");
	il2cpp_utils::GetFieldValue(&glowHue, self, "glowHue");
	il2cpp_utils::GetFieldValue(&glowSaturation, self, "glowSaturation");
	il2cpp_utils::GetFieldValue(&glowValue, self, "glowValue");
	il2cpp_utils::GetFieldValue(&enemyHue, self, "enemyHue");
	il2cpp_utils::GetFieldValue(&enemySaturation, self, "enemySaturation");
	il2cpp_utils::GetFieldValue(&enemyValue, self, "enemyValue");
	il2cpp_utils::GetFieldValue(&_customColors, self, "_customColors");
	il2cpp_utils::GetFieldValue(&_customEnemyColor, self, "_customEnemyColor");
	il2cpp_utils::GetFieldValue(&startingWall, self, "startingWall");
	il2cpp_utils::GetFieldValue(&endingWall, self, "endingWall");
	il2cpp_utils::GetFieldValue(&height, self, "height");
	il2cpp_utils::GetFieldValue(&groundHeight, self, "groundHeight");
	il2cpp_utils::GetFieldValue(&seed, self, "seed");
	il2cpp_utils::GetFieldValue(&start, self, "start");
	il2cpp_utils::GetFieldValue(&end, self, "end");
	il2cpp_utils::GetFieldValue(&min, self, "min");
	il2cpp_utils::GetFieldValue(&max, self, "max");
	il2cpp_utils::GetFieldValue(&extent, self, "extent");
	il2cpp_utils::GetFieldValue(&generateDebris, self, "generateDebris");
	il2cpp_utils::GetFieldValue(&debris, self, "debris");
	il2cpp_utils::GetFieldValue(&yStep, self, "yStep");
	il2cpp_utils::GetFieldValue(&zStep, self, "zStep");
	il2cpp_utils::GetFieldValue(&yOffsets, self, "yOffsets");
	il2cpp_utils::GetFieldValue(&zOffsets, self, "zOffsets");
	il2cpp_utils::GetFieldValue(&blocks, self, "blocks");
	il2cpp_utils::GetFieldValue(&size, self, "size");
	il2cpp_utils::GetFieldValue(&emptyBlocks, self, "emptyBlocks");
	il2cpp_utils::GetFieldValue(&decorationBlocks, self, "decorationBlocks");
	il2cpp_utils::GetFieldValue(&props, self, "props");
	il2cpp_utils::GetFieldValue(&lastDebrisPoint, self, "lastDebrisPoint");

	json j;
	j["derivedType"] = std::string(il2cpp_functions::class_get_name(klass));
	j["colorHue"] = colorHue;
	j["colorSaturation"] = colorSaturation;
	j["colorValue"] = colorValue;
	j["fogHue"] = fogHue;
	j["fogSaturation"] = fogSaturation;
	j["fogValue"] = fogValue;
	j["glowHue"] = glowHue;
	j["glowSaturation"] = glowSaturation;
	j["glowValue"] = glowValue;
	j["enemyHue"] = enemyHue;
	j["enemySaturation"] = enemySaturation;
	j["enemyValue"] = enemyValue;
	j["_customColors"] = _customColors;
	j["_customEnemyColor"] = _customEnemyColor;
	j["startingWall"] = startingWall;
	j["endingWall"] = endingWall;
	j["height"] = height;
	j["groundHeight"] = groundHeight;
	j["seed"] = seed;
	j["start"] = start;
	j["end"] = end;
	j["min"] = min;
	j["max"] = max;
	j["extent"] = extent;
	j["generateDebris"] = generateDebris;
	j["debris"] = debris;
	j["propSeed"] = propSeed;
	j["yStep"] = yStep;
	j["zStep"] = zStep;

	j["yOffsets"] = {};
	if (yOffsets != nullptr)
	{
		for (size_t i = 0; i < il2cpp_functions::array_length((Il2CppArray*)yOffsets); i++)
		{
			j["yOffsets"].push_back(yOffsets->values[i]);
		}
	}

	j["zOffsets"] = {};
	if (zOffsets != nullptr)
	{
		for (size_t i = 0; i < il2cpp_functions::array_length((Il2CppArray*)zOffsets); i++)
		{
			j["zOffsets"].push_back(zOffsets->values[i]);
		}
	}

	j["blocks"] = {};
	if (blocks != nullptr)
	{
		for (size_t i = 0; i < il2cpp_functions::array_length((Il2CppArray*)blocks); i++)
		{
			j["blocks"].push_back(blocks->values[i]);
		}
	}

	j["props"] = {};
	if (props != nullptr)
	{
		List<Il2CppObject*> propsList(props);
		for (size_t i = 0; i < propsList.Count(); i++)
		{
			WorldObject p(propsList[i]);
			j["props"].push_back(p.Dump());
		}
	}

	j["size"] = size;

	j["lastDebrisPoint"] = lastDebrisPoint;

	return j;
}

void TrackSection::LoadFilledSection(json j)
{
}

void to_json(json& j, const Debris& d)
{
	j = json{
		{"seed", d.seed},
		{"distribution", d.distribution},
		{"projection", d.projection},
		{"spread", d.spread},
		{"density", d.density},
		{"interval", d.interval},
		{"uniformity", d.uniformity},
		{"minSize", d.minSize},
		{"maxSize", d.maxSize},
		{"shape", d.shape},
		{"buildOnAir", d.buildOnAir},
		{"timing", d.timing}
	};
}

void from_json(const json& j, Debris& d) 
{
	//j.at("seed").get_to(d.seed);
	j.at("distribution").get_to(d.distribution);
	j.at("projection").get_to(d.projection);
	j.at("spread").get_to(d.spread);
	j.at("density").get_to(d.density);
	j.at("interval").get_to(d.interval);
	j.at("uniformity").get_to(d.uniformity);
	j.at("minSize").get_to(d.minSize);
	j.at("maxSize").get_to(d.maxSize);
	j.at("shape").get_to(d.shape);
	j.at("timing").get_to(d.timing);
}