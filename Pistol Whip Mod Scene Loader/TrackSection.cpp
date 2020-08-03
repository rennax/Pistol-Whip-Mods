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
	return nullptr;
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

void to_json(json j, const Debris& d)
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
