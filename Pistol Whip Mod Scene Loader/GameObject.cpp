#include "GameObject.hpp"

namespace GameObject {
	Il2CppObject* emptyPrefab = nullptr;
	std::map<std::tuple<std::string, std::string>, Il2CppObject*> componentTypes;

	std::string ClassInfoDump(Il2CppClass* klass);

	Il2CppObject* GetComponentType(Il2CppObject* gameObject, std::string_view namespaze, std::string_view klassName) {
		std::tuple<std::string, std::string> klassKey = { namespaze.data(), klassName.data() };
		auto search = componentTypes.find(klassKey);
		if (search != componentTypes.end())
		{
			return search->second;
		}

		auto klass = il2cpp_utils::GetClassFromName(namespaze.data(), klassName.data());
		if (!klass)
		{
			LOG("ERROR: GameObject: GetComponentType failed, no class for: %s::%s", namespaze.data(), klassName.data());
			return nullptr;
		}

		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
		if (!type)
		{
			LOG("ERROR: GameObject: GetComponentType failed to get Il2CppObject for klass: %s::%s", namespaze.data(), klassName.data());
			return nullptr;
		}
		componentTypes.try_emplace(klassKey, type);
		return type;
	}

	Il2CppObject* InstantiateEmpty(Vector3 position, Quaternion rotation)
	{
		if (emptyPrefab == nullptr)
		{
			emptyPrefab = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject"));
			il2cpp_utils::RunMethod(emptyPrefab, ".ctor");
		}
		Il2CppObject* obj = nullptr;
		if (!il2cpp_utils::RunMethod(&obj, il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "Instantiate", emptyPrefab, &position, &rotation))
			LOG("Failed to Instantiate empty gameobject\n");
		return obj;
	}

	bool AddComponent(Il2CppObject* object, Il2CppObject* type)
	{
		return il2cpp_utils::RunMethod(object, "AddComponent", type);		
	}

	void AddComponent(Il2CppObject* object, Il2CppClass* klass)
	{
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
		if (type == nullptr)
		{
			LOG("Failed to get type of %s\n", ClassInfoDump(klass).c_str());
		}
		
		if (!AddComponent(object, type))
			LOG("Failed to add component %s, are you sure it is a component?\n", ClassInfoDump(klass).c_str());
	}

	void SetName(Il2CppObject* object, std::string_view name)
	{
		Il2CppString* CSName = il2cpp_utils::createcsstr(name);
		if (!il2cpp_utils::RunMethod(object, "set_name", CSName))
			LOG("Failed to set new name: %s\n", name.data());
	}


	std::string ClassInfoDump(Il2CppClass* klass) {
		std::string toRtn;
		toRtn += il2cpp_functions::class_get_namespace(klass);
		toRtn += ".";
		toRtn += il2cpp_functions::class_get_name(klass);
		return toRtn;
	}
}
