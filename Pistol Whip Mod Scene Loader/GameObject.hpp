#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <map>
#include <string>
#include <string_view>


using json = nlohmann::json;

namespace GameObject
{
	

	Il2CppObject* GetComponentType(Il2CppObject* gameObject, std::string_view namespaze, std::string_view klassName);

	Il2CppObject* InstantiateEmpty(Vector3 position, Quaternion rotation);
	Il2CppObject* AddComponent(Il2CppObject* object, Il2CppObject* type);
	Il2CppObject* AddComponent(Il2CppObject* object, Il2CppClass* klass);
	Il2CppObject* AddComponent(Il2CppObject* object, std::string_view namespaze, std::string_view className);
	void SetName(Il2CppObject* object, std::string_view name);

};


#endif // !GAMEOBJECT_HPP
