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
	bool AddComponent(Il2CppObject* object, Il2CppObject* type);
	void AddComponent(Il2CppObject* object, Il2CppClass* klass);
	void SetName(Il2CppObject* object, std::string_view name);

};


#endif // !GAMEOBJECT_HPP
