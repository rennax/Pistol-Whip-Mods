#include "WorldObject.hpp"

WorldObject::WorldObject(WorldPoint point_, Il2CppObject* prefab_, Vector3 scale_) :
	point(point_), prefab(prefab_), scale(scale_)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "WorldObject");
	worldObject = il2cpp_functions::object_new(klass);

	const auto ctor = il2cpp_utils::GetMethod(klass, ".ctor", 3);
	il2cpp_utils::RunMethod(worldObject, ctor, &point, prefab, &scale);
}

WorldObject::WorldObject(WorldPoint point_, Il2CppObject* prefab_) :
	point(point_), prefab(prefab_), scale({ 1,1,1 })
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