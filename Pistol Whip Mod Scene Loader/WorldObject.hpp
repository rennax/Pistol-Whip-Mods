#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "utils.h"
#include <string_view>
#include "List.hpp"
struct WorldPoint;

typedef struct WorldPoint {
	Vector3 position;
	Quaternion rotation;
	//static WorldPoint identity;
} WorldPoint;


class WorldObject
{
public:
	WorldObject(WorldPoint point, Il2CppObject* prefab, Vector3 scale);
	WorldObject(WorldPoint point, Il2CppObject* prefab);
	~WorldObject();
	static Il2CppObject* GetWorldObjectByName(Il2CppObject* levelData, std::string_view prefabName) {
		auto tmpWorldObjects = il2cpp_utils::GetFieldValue(levelData, "simpleStaticWorldObjects");
		CSharp::List<Il2CppObject*> worldObjects(tmpWorldObjects);
		LOG("Dumping names of all objects in LevelData::WorldObjects\n");
		for (size_t i = 0; i < worldObjects.Count(); i++)
		{
			auto pref = il2cpp_utils::GetFieldValue(worldObjects[i], "prefab");
			auto name = GetObjectName(pref);
			LOG("\t%s\n", name.c_str());
		}
		return nullptr;
	}

private:
	static std::string GetObjectName(Il2CppObject* obj) {
		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Object");
		auto method = il2cpp_utils::GetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "GetName", 1);
		Il2CppString* str = nullptr;
		il2cpp_utils::RunMethod(&str, klass, "GetName", obj);
		auto name = csstrtostr(str);
		return std::string(to_utf8(name));
	}

private:
	Il2CppObject* worldObject;
	WorldPoint point;
	Il2CppObject* prefab;
	Vector3 scale;
};

WorldObject::WorldObject(WorldPoint point_, Il2CppObject* prefab_, Vector3 scale_) :
	point(point_), prefab(prefab_), scale(scale_)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "WorldObject");
	worldObject = il2cpp_functions::object_new(klass);

	const auto ctor = il2cpp_utils::GetMethod(klass, ".ctor", 3);
	il2cpp_utils::RunMethod(worldObject, ctor, &point, prefab, &scale);
}

WorldObject::WorldObject(WorldPoint point_, Il2CppObject* prefab_) :
	point(point_), prefab(prefab_), scale({1,1,1})
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "WorldObject");
	worldObject = il2cpp_functions::object_new(klass);

	const auto ctor = il2cpp_utils::GetMethod(klass, ".ctor", 2);
	il2cpp_utils::RunMethod(worldObject, ctor, &point, prefab);

	il2cpp_utils::GetFieldValue(&scale, worldObject, "scale");
}

WorldObject::~WorldObject()
{
}

#endif // !WORLDOBJECT_HPP


