#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "utils.h"
#include <string_view>
#include "List.hpp"
struct WorldPoint;

typedef struct WorldPoint {
	Vector3 position;
	Quaternion rotation;
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
		//LOG("Dumping names of all objects in LevelData::WorldObjects\n");
		//for (size_t i = 0; i < worldObjects.Count(); i++)
		//{
		//	auto pref = il2cpp_utils::GetFieldValue(worldObjects[i], "prefab");
		//	auto name = GetObjectName(pref);
		//	LOG("\t%s\n", name.c_str());
		//}
		return nullptr;
	}
	Il2CppObject* GetObj() {
		return worldObject;
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



#endif // !WORLDOBJECT_HPP


