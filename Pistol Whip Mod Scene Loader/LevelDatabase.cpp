#include "LevelDatabase.hpp"
#include "utils.h"



namespace LevelDatabase {

MAKE_HOOK(ctor, void, void* self)
{
	LOG("levelDatabaseCTOR() hook called");
	ctor_orig(self);

	//auto levelDatabase = il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(self), "levelDB");
	//LevelCount(levelDatabase);
	//DublicateLevelLastLevel(levelDatabase);
	//LevelCount(levelDatabase);
}

MAKE_HOOK(Init, void, void* self)
{
	LOG("LevelDatabase.Init() hook called\n");


	Init_orig(self);
}

void initHooks(funchook_t* funchookp)
{
	LOG("LevelDatabase::initHooks()\n");
	Init_orig = (Init_t)il2cpp_utils::GetMethod("", "LevelDatabase", "Init", 0)->methodPointer;
	INSTALL_HOOK(Init);

	ctor_orig = (ctor_t)il2cpp_utils::GetMethod("", "LevelDatabase", ".ctor", 0)->methodPointer;
	INSTALL_HOOK(ctor);
}

Il2CppObject* GetLevelData(Il2CppObject* levelDatabase)
{
	// Is of type List<LevelData>
	//LOG("Attempting to get field value from \"levelData\" field\n");
	return il2cpp_utils::GetFieldValue(reinterpret_cast<Il2CppObject*>(levelDatabase), "levelData");
}


void LevelCount(Il2CppObject* levelDatabase)
{
	auto levelData = GetLevelData(levelDatabase);
	// Get the count property from levelData list
	Il2CppClass* tmpClass = il2cpp_functions::object_get_class(levelData);
	const PropertyInfo* propInfo = il2cpp_functions::class_get_property_from_name(tmpClass, "Count");
	const MethodInfo* methodGet = propInfo->get;

	//Call methodGet and print count of levels
	int tmpOut;
	if (!il2cpp_utils::RunMethod(&tmpOut, (void*)levelData, methodGet))
	{
		LOG("Failed to call LevelDatabase.levelData.count from LevelDatabaseInit_hook()\n");
		return;
	}
	int count = tmpOut;
	LOG("levelDatabase.levelData.Count: %d\n", count);
}

void DublicateLevelLastLevel(Il2CppObject* levelDatabase)
{
	static bool run = true;// Run this onces, we dont want to keep dublicating
	if (run)
	{
		auto levelData = GetLevelData(levelDatabase);
		Il2CppClass* lvlDataClass = il2cpp_functions::object_get_class(levelData);
		const PropertyInfo* propInfo = il2cpp_functions::class_get_property_from_name(lvlDataClass, "Item");
		const MethodInfo* methodAdd = il2cpp_utils::GetMethod(lvlDataClass, "Add", 1);
		const MethodInfo* methodBuildDictionaries = il2cpp_utils::GetMethod(levelDatabase->klass, "BuildDictionaries", 0);

		int highestLevelIndex;
		bool test = il2cpp_utils::GetFieldValue(&highestLevelIndex, levelDatabase, "highestLevelIndex");
		LOG("highestLevelIndex: %d\n", highestLevelIndex);

		Il2CppObject tmpOut;
		int index = 12;
		if (!il2cpp_utils::RunMethod(&tmpOut, (void*)levelData, propInfo->get, &index))
		{
			LOG("Failed to call LevelDatabase.levelData.Item\n");
			return;
		}
		//Push map index 13 back onto levelData
		if (!il2cpp_utils::RunMethod((void*)levelData, methodAdd, &tmpOut))
		{
			LOG("Failed to call LevelDatabase.levelData.Add()\n");
			return;
		}

		////Rebuild Dictionaries
		//if (!il2cpp_utils::RunMethod((void*)levelDatabase, methodBuildDictionaries))
		//{
		//	LOG("Failed to call LevelDatabase.BuildDictionaries()\n");
		//	return;
		//}

		run = false;
	}
}

};

