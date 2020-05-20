#include "WorldObject.hpp"
#include "LODSwitcher.hpp"


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

WorldObject::WorldObject(Il2CppObject* obj)
{
	worldObject = obj;
}

Il2CppObject* WorldObject::Dump(Il2CppObject* levelData, std::string_view prefabName) {
	auto tmpWorldObjects = il2cpp_utils::GetFieldValue(levelData, "simpleStaticWorldObjects");
	CSharp::List<Il2CppObject*> worldObjects(tmpWorldObjects);

	if (worldObjects.Count() > 0)
	{
		auto pref = il2cpp_utils::GetFieldValue(worldObjects[0], "prefab");
		auto name = GetObjectName(pref);
		LOG("\tGetting components in %s:\n\n");
		WorldObject::DumpComponents(pref);
	}

	return nullptr;
}

std::string WorldObject::GetObjectName(Il2CppObject* obj) {
	auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Object");
	auto method = il2cpp_utils::GetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "GetName", 1);
	Il2CppString* str = nullptr;
	il2cpp_utils::RunMethod(&str, klass, "GetName", obj);
	auto name = csstrtostr(str);
	return std::string(to_utf8(name));
}

void WorldObject::DumpComponents(Il2CppObject* prefab) {
	auto GetComponents = (GetComponents_t)il2cpp_functions::resolve_icall("UnityEngine.GameObject::GetComponentsInternal(System.Type, System.Boolean, System.Boolean, System.Boolean, System.Boolean, System.Object)");
	auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Component");
	std::vector<Il2CppObject*> componentsFound;
	auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
	Il2CppArray* objects = GetComponents(prefab, type, false, true, true, false, nullptr);

	for (int i = 0; i < il2cpp_functions::array_length(objects); i++) {
		Il2CppObject* object = il2cpp_array_get(objects, Il2CppObject*, i);
		if (object != nullptr) {
			Il2CppString* nameObject;
			il2cpp_functions::class_get_name(il2cpp_functions::object_get_class(object));
			//il2cpp_utils::RunMethod(&nameObject, object, "get_name");
			//componentsFound.push_back(object);
			LOG("\tComponent name: %s\n", il2cpp_functions::class_get_name(il2cpp_functions::object_get_class(object)));
			if (std::string(il2cpp_functions::class_get_name(il2cpp_functions::object_get_class(object))) == std::string("LODSwitcher"))
			{
				LODSwitcher::Dump(object);
			}
		}
	}
}

WorldObject::~WorldObject()
{
}