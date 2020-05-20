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
	WorldObject(Il2CppObject* obj);
	~WorldObject();
	static Il2CppObject* Dump(Il2CppObject* levelData, std::string_view prefabName);
	Il2CppObject* GetObj() {
		return worldObject;
	}
	static void DumpComponents(Il2CppObject* prefab);
private:
	static std::string GetObjectName(Il2CppObject* obj);

	static Il2CppArray* (*GetComponents)(void* self, Il2CppObject* type, bool useSearchTypeAsArrayReturnType, bool recursive, bool includeInactive, bool reverse, Il2CppObject* resultList);
	typedef Il2CppArray* (*GetComponents_t)(void* self, Il2CppObject* type, bool useSearchTypeAsArrayReturnType, bool recursive, bool includeInactive, bool reverse, Il2CppObject* resultList);

	

private:
	Il2CppObject* worldObject;
	WorldPoint point;
	Il2CppObject* prefab;
	Vector3 scale;
};



#endif // !WORLDOBJECT_HPP


