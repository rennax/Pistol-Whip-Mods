#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <map>
#include <string>
#include <string_view>


using json = nlohmann::json;

class GameObject
{
public:
	GameObject(Il2CppObject* obj);
	~GameObject();
	json DumpObject(Il2CppObject* obj);
private:

};

std::map<std::tuple<std::string, std::string>, Il2CppObject*> componentTypes;

Il2CppObject* GetComponentType(Il2CppObject* gameObject, std::string_view namespaze, std::string_view klassName) {
	std::tuple<std::string, std::string> klassKey = {namespaze.data(), klassName.data()};
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

#endif // !GAMEOBJECT_HPP
