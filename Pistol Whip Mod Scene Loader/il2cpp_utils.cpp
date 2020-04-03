#include "il2cpp_utils.hpp"
#include <sstream>
#include "logger.h"

// Many implementaions from https://github.com/sc2ad/pistol-whip-hook/blob/fd7edc3d1d39d231e43c1430dbf4336045a056cc/shared/utils/il2cpp-utils.cpp
namespace il2cpp_utils {
	using namespace std;
	const MethodInfo* GetMethod(Il2CppClass* klass, std::string_view methodName, int argsCount) {
		if (!klass) return nullptr;
		auto methodInfo = il2cpp_functions::class_get_method_from_name(klass, methodName.data(), argsCount);
		if (!methodInfo) {
			LOG("ERROR: could not find method %s with %i parameters in class %s (namespace '%s')!", methodName.data(),
				argsCount, il2cpp_functions::class_get_name(klass), il2cpp_functions::class_get_namespace(klass));
			return nullptr;
		}
		return methodInfo;
	}

	const MethodInfo* GetMethod(std::string_view nameSpace, std::string_view className, std::string_view methodName, int argsCount) {
		return GetMethod(GetClassFromName(nameSpace.data(), className.data()), methodName, argsCount);
	}

	const PropertyInfo* GetProperty(Il2CppClass* klass, std::string_view propertyName) {
		if (!klass) {
			LOG("ERROR: GetProperty: parameter klass is nullptr");
			return nullptr;
		}
		const PropertyInfo* prop = il2cpp_functions::class_get_property_from_name(klass, propertyName.data());
		if (!prop)
		{
			LOG("WARNING: GetProperty: class %s does not contain property %s", 
				il2cpp_functions::class_get_name(klass),
				propertyName.data());
			return nullptr;
		}
		return prop;
	}

	const MethodInfo* GetPropertyGetMethod(Il2CppClass* klass, std::string_view propertyName) {
		if (!klass) {
			LOG("ERROR: GetPropertyGetMethod: parameter klass is nullptr");
			return nullptr;
		}
		const PropertyInfo* prop = GetProperty(klass, propertyName);
		if (!prop)
		{
			return nullptr;
		}
		const MethodInfo* method = il2cpp_functions::property_get_get_method(prop);
		if (!method)
		{
			LOG("WARNING: GetPropertyGetMethod: class %s does not contain property %s with get field",
				il2cpp_functions::class_get_name(klass),
				propertyName.data());
			return nullptr;
		}
		return method;
	}

	const MethodInfo* GetPropertySetMethod(Il2CppClass* klass, std::string_view propertyName) {
		if (!klass) {
			LOG("ERROR: GetPropertySetMethod: parameter klass is nullptr");
			return nullptr;
		}
		const PropertyInfo* prop = GetProperty(klass, propertyName);
		if (!prop)
		{
			return nullptr;
		}
		const MethodInfo* method = il2cpp_functions::property_get_set_method(prop);
		if (!method)
		{
			LOG("WARNING: GetPropertySetMethod: class %s does not contain property %s with set field",
				il2cpp_functions::class_get_name(klass),
				propertyName.data());
			return nullptr;
		}
		return method;
	}

	// Returns a legible string from an Il2CppException*
	std::string ExceptionToString(Il2CppException* exp) {
		char msg[EXCEPTION_MESSAGE_SIZE];
		il2cpp_functions::format_exception(exp, msg, EXCEPTION_MESSAGE_SIZE);
		// auto exception_message = csstrtostr(exp->message);
		// return to_utf8(exception_message);
		return msg;
	}

	FieldInfo* FindField(Il2CppClass* klass, std::string_view fieldName) {
		if (!klass) return nullptr;
		auto field = il2cpp_functions::class_get_field_from_name(klass, fieldName.data());
		if (!field) {
			LOG("could not find field %s in class %s (namespace '%s')!", fieldName.data(),
				il2cpp_functions::class_get_name(klass), il2cpp_functions::class_get_namespace(klass));
		}
		return field;
	}

	bool SetFieldValue(Il2CppObject* instance, FieldInfo* field, void* value) {
		if (!field) {
			LOG("il2cpp_utils: SetFieldValue: Null field parameter!");
			return false;
		}
		if (instance) {
			il2cpp_functions::field_set_value(instance, field, value);
		}
		else { // Fallback to perform a static field set
			il2cpp_functions::field_static_set_value(field, value);
		}
		return true;
	}


	Il2CppArray* CreateIl2CppArray(const char* name_space, const char* type_name, size_t array_size)
	{
		Il2CppClass* klass = GetClassFromName(name_space, type_name);
		if (!klass)
		{
			LOG("il2cpp_utils: CreateArray: Couldn't get Il2CppClass from provide namespace and type name");
			return nullptr;
		}
		auto arr = il2cpp_functions::array_new(klass, array_size);
		return arr;
	}


	bool SetFieldValue(Il2CppClass* klass, std::string_view fieldName, void* value) {
		if (!klass) {
			LOG("il2cpp_utils: SetFieldValue: Null klass parameter!");
			return false;
		}
		auto field = FindField(klass, fieldName);
		if (!field) return false;
		return SetFieldValue(nullptr, field, value);
	}

	bool SetFieldValue(Il2CppObject* instance, std::string_view fieldName, void* value) {
		if (!instance) {
			LOG("il2cpp_utils: SetFieldValue: Null instance parameter!");
			return false;
		}
		auto klass = il2cpp_functions::object_get_class(instance);
		if (!klass) {
			LOG("il2cpp_utils: SetFieldValue: Could not find object class!");
			return false;
		}
		auto field = FindField(klass, fieldName);
		if (!field) return false;
		return SetFieldValue(instance, field, value);
	}

	Il2CppReflectionType* MakeGenericType(Il2CppReflectionType* gt, Il2CppArray* types) {

		auto runtimeType = GetClassFromName("System", "RuntimeType");
		if (!runtimeType) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed to get System.RuntimeType!");
			return nullptr;
		}
		auto makeGenericMethod = il2cpp_functions::class_get_method_from_name(runtimeType, "MakeGenericType", 2);
		if (!makeGenericMethod) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed to get RuntimeType.MakeGenericType(param1, param2) method!");
			return nullptr;
		}

		Il2CppException* exp = nullptr;
		void* params[] = { reinterpret_cast<void*>(gt), reinterpret_cast<void*>(types) };
		auto genericType = il2cpp_functions::runtime_invoke(makeGenericMethod, nullptr, params, &exp);
		if (exp) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed with exception: %s", ExceptionToString(exp).c_str());
			return nullptr;
		}
		return reinterpret_cast<Il2CppReflectionType*>(genericType);
	}

	Il2CppClass* MakeGeneric(const Il2CppClass* klass, std::initializer_list<const Il2CppClass*> args) {

		auto typ = GetClassFromName("System", "Type");
		if (!typ) {
			return nullptr;
		}
		auto getType = il2cpp_functions::class_get_method_from_name(typ, "GetType", 1);
		if (!getType) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get System.Type.GetType(param1) method!");
			return nullptr;
		}

		auto klassType = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
		if (!klassType) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get class type object!");
			return nullptr;
		}

		// Call Type.MakeGenericType on it
		auto a = il2cpp_functions::array_new_specific(typ, args.size());
		if (!a) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to make new array with length: %zu", args.size());
			return nullptr;
		}

		int i = 0;
		for (auto arg : args) {
			auto t = il2cpp_functions::class_get_type_const(arg);
			auto o = il2cpp_functions::type_get_object(t);
			if (!o) {
				LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get type for %s", il2cpp_functions::class_get_name_const(arg));
				return nullptr;
			}
			il2cpp_array_set(a, void*, i, reinterpret_cast<void*>(o));
			i++;
		}

		auto reflection_type = MakeGenericType(reinterpret_cast<Il2CppReflectionType*>(klassType), a);
		if (!reflection_type) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to MakeGenericType from Il2CppReflectionType and Il2CppArray!");
			return nullptr;
		}

		auto ret = il2cpp_functions::class_from_system_type(reinterpret_cast<Il2CppReflectionType*>(reflection_type));
		if (!ret) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get class from Il2CppReflectionType!");
			return nullptr;
		}
		LOG("DEBUG: il2cpp_utils: MakeGeneric: returning %s", il2cpp_functions::class_get_name(ret));
		return ret;
	}

	Il2CppClass* GetClassFromName(const char* name_space, const char* type_name) {

		auto dom = il2cpp_functions::domain_get();
		if (!dom) {
			LOG("ERROR: GetClassFromName: Could not get domain!");
			return nullptr;
		}
		size_t assemb_count;
		const Il2CppAssembly** allAssemb = il2cpp_functions::domain_get_assemblies(dom, &assemb_count);

		for (int i = 0; i < assemb_count; i++) {
			auto assemb = allAssemb[i];
			auto img = il2cpp_functions::assembly_get_image(assemb);
			if (!img) {
				LOG("ERROR: Assembly with name: %s has a null image!", assemb->aname.name);
				continue;
			}
			auto klass = il2cpp_functions::class_from_name(img, name_space, type_name);
			if (klass) {
				return klass;
			}
		}
		LOG("ERROR: il2cpp_utils: GetClassFromName: Could not find class with namepace: %s and name: %s", name_space, type_name);
		return nullptr;
	}

	bool ParameterMatch(const MethodInfo* method, Il2CppType** type_arr, int count) {

		if (method->parameters_count != count) {
			return false;
		}
		for (int i = 0; i < method->parameters_count; i++) {
			if (!il2cpp_functions::type_equals(method->parameters[i].parameter_type, type_arr[i])) {
				return false;
			}
		}
		return true;
	}

	
}

