#include "il2cpp_utils.hpp"
#include <sstream>
#include <algorithm>
#include "logger.h"
#include <utility>

// Many implementaions from https://github.com/sc2ad/pistol-whip-hook/blob/fd7edc3d1d39d231e43c1430dbf4336045a056cc/shared/utils/il2cpp-utils.cpp
namespace il2cpp_utils {

	//#define DEFINE_IL2CPP_ARG_TYPE(type, nameSpace, className) \
 //       template<> \
 //       struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type> { \
 //           static inline Il2CppClass* get() { \
 //               il2cpp_functions::Init(); \
 //               return il2cpp_utils::GetClassFromName(nameSpace, className); \
 //           } \
 //       }
	//DEFINE_IL2CPP_ARG_TYPE(Il2CppReflectionMethod*, "System.Reflection", "MethodInfo");


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
			LOG("ERROR: GetProperty: parameter klass is nullptr\n");
			return nullptr;
		}
		const PropertyInfo* prop = il2cpp_functions::class_get_property_from_name(klass, propertyName.data());
		if (!prop)
		{
			LOG("WARNING: GetProperty: class %s does not contain property %s\n", 
				il2cpp_functions::class_get_name(klass),
				propertyName.data());
			return nullptr;
		}
		return prop;
	}

	const MethodInfo* GetPropertyGetMethod(Il2CppClass* klass, std::string_view propertyName) {
		if (!klass) {
			LOG("ERROR: GetPropertyGetMethod: parameter klass is nullptr\n");
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
			LOG("WARNING: GetPropertyGetMethod: class %s does not contain property %s with get field\n",
				il2cpp_functions::class_get_name(klass),
				propertyName.data());
			return nullptr;
		}
		return method;
	}

	const MethodInfo* GetPropertySetMethod(Il2CppClass* klass, std::string_view propertyName) {
		if (!klass) {
			LOG("ERROR: GetPropertySetMethod: parameter klass is nullptr\n");
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
			LOG("WARNING: GetPropertySetMethod: class %s does not contain property %s with set field\n",
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
			LOG("could not find field %s in class %s (namespace '%s')!\n", fieldName.data(),
				il2cpp_functions::class_get_name(klass), il2cpp_functions::class_get_namespace(klass));
		}
		return field;
	}

	bool SetFieldValue(Il2CppObject* instance, FieldInfo* field, void* value) {
		if (!field) {
			LOG("il2cpp_utils: SetFieldValue: Null field parameter!\n");
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
			LOG("il2cpp_utils: CreateArray: Couldn't get Il2CppClass from provide namespace and type name\n");
			return nullptr;
		}
		auto arr = il2cpp_functions::array_new(klass, array_size);
		return arr;
	}


	bool SetFieldValue(Il2CppClass* klass, std::string_view fieldName, void* value) {
		if (!klass) {
			LOG("il2cpp_utils: SetFieldValue: Null klass parameter!\n");
			return false;
		}
		auto field = FindField(klass, fieldName);
		if (!field) return false;
		return SetFieldValue(nullptr, field, value);
	}

	bool SetFieldValue(Il2CppObject* instance, std::string_view fieldName, void* value) {
		if (!instance) {
			LOG("il2cpp_utils: SetFieldValue: Null instance parameter!\n");
			return false;
		}
		auto klass = il2cpp_functions::object_get_class(instance);
		if (!klass) {
			LOG("il2cpp_utils: SetFieldValue: Could not find object class!\n");
			return false;
		}
		auto field = FindField(klass, fieldName);
		if (!field) return false;
		return SetFieldValue(instance, field, value);
	}

	Il2CppReflectionType* MakeGenericType(Il2CppReflectionType* gt, Il2CppArray* types) {

		auto runtimeType = GetClassFromName("System", "RuntimeType");
		if (!runtimeType) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed to get System.RuntimeType!\n");
			return nullptr;
		}
		auto makeGenericMethod = il2cpp_functions::class_get_method_from_name(runtimeType, "MakeGenericType", 2);
		if (!makeGenericMethod) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed to get RuntimeType.MakeGenericType(param1, param2) method!\n");
			return nullptr;
		}

		Il2CppException* exp = nullptr;
		void* params[] = { reinterpret_cast<void*>(gt), reinterpret_cast<void*>(types) };
		auto genericType = il2cpp_functions::runtime_invoke(makeGenericMethod, nullptr, params, &exp);
		if (exp) {
			LOG("ERROR: il2cpp_utils: MakeGenericType: Failed with exception: %s\n", ExceptionToString(exp).c_str());
			return nullptr;
		}
		return reinterpret_cast<Il2CppReflectionType*>(genericType);
	}


	const MethodInfo* MakeGeneric(const MethodInfo* info, std::initializer_list<Il2CppClass*> args) {

		// Ensure it is generic
		if (!il2cpp_functions::method_is_generic(info)) {
			return nullptr;
		}
		// Create the Il2CppReflectionMethod* from the MethodInfo* using the MethodInfo's type
		auto* infoObj = il2cpp_functions::method_get_object(info, nullptr);
		// Populate generic parameters into array
		static auto* typeClass = il2cpp_utils::GetClassFromName("System", "Type");
		Array<Il2CppObject*>* arr = reinterpret_cast<Array<Il2CppObject*>*>(il2cpp_functions::array_new(typeClass, args.size()));
		int i = 0;
		for (auto* klass : args) {
			arr->values[i] = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
			i++;
		}
		//Il2CppObject* rbo = nullptr;
		//il2cpp_utils::RunMethod(&rbo, (Il2CppObject*)infoObj, "MakeGenericMethod", arr);

		// Call instance function on infoObj to MakeGeneric
		Il2CppReflectionMethod* returnedInfoObj = nullptr;
		il2cpp_utils::RunMethod(&returnedInfoObj, (Il2CppObject*)infoObj, "MakeGenericMethod", arr);
		// Get MethodInfo* back from generic instantiated method
		const auto* inflatedInfo = il2cpp_functions::method_get_from_reflection(returnedInfoObj);
		// Return method to be invoked by caller
		return inflatedInfo;
		// Ex:

	}

	Il2CppClass* MakeGeneric(const Il2CppClass* klass, std::initializer_list<const Il2CppClass*> args) {

		auto typ = GetClassFromName("System", "Type");
		if (!typ) {
			return nullptr;
		}
		auto getType = il2cpp_functions::class_get_method_from_name(typ, "GetType", 1);
		if (!getType) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get System.Type.GetType(param1) method!\n");
			return nullptr;
		}

		auto klassType = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
		if (!klassType) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get class type object!\n");
			return nullptr;
		}

		// Call Type.MakeGenericType on it
		auto a = il2cpp_functions::array_new_specific(typ, args.size());
		if (!a) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to make new array with length: %zu\n", args.size());
			return nullptr;
		}

		int i = 0;
		for (auto arg : args) {
			auto t = il2cpp_functions::class_get_type_const(arg);
			auto o = il2cpp_functions::type_get_object(t);
			if (!o) {
				LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get type for %s\n", il2cpp_functions::class_get_name_const(arg));
				return nullptr;
			}
			il2cpp_array_set(a, void*, i, reinterpret_cast<void*>(o));
			i++;
		}

		auto reflection_type = MakeGenericType(reinterpret_cast<Il2CppReflectionType*>(klassType), a);
		if (!reflection_type) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to MakeGenericType from Il2CppReflectionType and Il2CppArray!\n");
			return nullptr;
		}

		auto ret = il2cpp_functions::class_from_system_type(reinterpret_cast<Il2CppReflectionType*>(reflection_type));
		if (!ret) {
			LOG("ERROR: il2cpp_utils: MakeGeneric: Failed to get class from Il2CppReflectionType!\n");
			return nullptr;
		}
		LOG("DEBUG: il2cpp_utils: MakeGeneric: returning %s\n", il2cpp_functions::class_get_name(ret));
		return ret;
	}

	Il2CppClass* GetClassFromName(const char* name_space, const char* type_name) {

		auto dom = il2cpp_functions::domain_get();
		if (!dom) {
			LOG("ERROR: GetClassFromName: Could not get domain!\n");
			return nullptr;
		}
		size_t assemb_count;
		const Il2CppAssembly** allAssemb = il2cpp_functions::domain_get_assemblies(dom, &assemb_count);

		for (int i = 0; i < assemb_count; i++) {
			auto assemb = allAssemb[i];
			auto img = il2cpp_functions::assembly_get_image(assemb);
			if (!img) {
				LOG("ERROR: Assembly with name: %s has a null image!\n", assemb->aname.name);
				continue;
			}
			auto klass = il2cpp_functions::class_from_name(img, name_space, type_name);
			if (klass) {
				return klass;
			}
		}
		LOG("ERROR: il2cpp_utils: GetClassFromName: Could not find class with namepace: %s and name: %s\n", name_space, type_name);
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

	
	Il2CppString* createcsstr(std::string_view inp)
	{
		return il2cpp_functions::string_new_len(inp.data(), (uint32_t)inp.length());
	}


	bool IsConvertible(const Il2CppType* to, const Il2CppType* from) {
		if (to->byref) {
			if (!from->byref) {
				LOG("DEBUG: IsConvertible: to (%s, %p) is ref/out while from (%s, %p) is not. Not convertible.\n",
					TypeGetSimpleName(to), to, TypeGetSimpleName(from), from);
				return false;
			}
			else {
				LOG("DEBUG: IsConvertible: to (%s, %p) and from (%s, %p) are both ret/out. May be convertible.\n",
					TypeGetSimpleName(to), to, TypeGetSimpleName(from), from);
			}
		}
		auto classTo = il2cpp_functions::class_from_il2cpp_type(to);
		auto classFrom = il2cpp_functions::class_from_il2cpp_type(from);
		auto ret = il2cpp_functions::class_is_assignable_from(classTo, classFrom);
		/*LOG("DEBUG: IsConvertible: class_is_assignable_from(%s, %s) returned %s",
			ClassStandardName(classTo).c_str(), ClassStandardName(classFrom).c_str(), ret ? "true" : "false");*/
		if (!ret && il2cpp_functions::class_is_enum(classTo)) {
			LOG("DEBUG: IsConvertible: but classTo is enum! Comparing against class_enum_basetype.\n");
			ret = IsConvertible(il2cpp_functions::class_enum_basetype(classTo), from);
		}
		return ret;
	}


	bool ParameterMatch(const MethodInfo* method, const Il2CppType* const* type_arr, decltype(MethodInfo::parameters_count) count) {

		if (method->parameters_count != count) {
			return false;
		}
		// TODO: supply boolStrictMatch and use type_equals instead of IsConvertible if supplied?
		for (decltype(method->parameters_count) i = 0; i < method->parameters_count; i++) {
			// TODO: just because two parameter lists match doesn't necessarily mean this is the best match...
			if (!(IsConvertible(method->parameters[i].parameter_type, type_arr[i]))) {
				return false;
			}
		}
		return true;
	}

	static std::unordered_map<Il2CppClass*, const char*> typeMap;

	// TODO: somehow append "out/ref " to the front if type->byref? Make a TypeStandardName?
	const char* TypeGetSimpleName(const Il2CppType* type) {

		if (typeMap.empty()) {
			typeMap[il2cpp_functions::defaults->boolean_class] = "bool";
			typeMap[il2cpp_functions::defaults->byte_class] = "byte";
			typeMap[il2cpp_functions::defaults->sbyte_class] = "sbyte";
			typeMap[il2cpp_functions::defaults->char_class] = "char";
			typeMap[il2cpp_functions::defaults->single_class] = "float";
			typeMap[il2cpp_functions::defaults->double_class] = "double";
			typeMap[il2cpp_functions::defaults->int16_class] = "short";
			typeMap[il2cpp_functions::defaults->uint16_class] = "ushort";
			typeMap[il2cpp_functions::defaults->int32_class] = "int";
			typeMap[il2cpp_functions::defaults->uint32_class] = "uint";
			typeMap[il2cpp_functions::defaults->int64_class] = "long";
			typeMap[il2cpp_functions::defaults->uint64_class] = "ulong";
			typeMap[il2cpp_functions::defaults->object_class] = "object";
			typeMap[il2cpp_functions::defaults->string_class] = "string";
			typeMap[il2cpp_functions::defaults->void_class] = "void";
		}
		auto p = typeMap.find(il2cpp_functions::class_from_type(type));
		if (p != typeMap.end()) {
			return p->second;
		}
		else {
			return il2cpp_functions::type_get_name(type);
		}
	}


	std::string ClassStandardName(Il2CppClass* klass, bool generics) {
		std::stringstream ss;
		const char* namespaze = il2cpp_functions::class_get_namespace(klass);
		auto* declaring = il2cpp_functions::class_get_declaring_type(klass);
		bool hasNamespace = (namespaze && namespaze[0] != '\0');
		if (!hasNamespace && declaring) {
			ss << ClassStandardName(declaring, false) << "/";
		}
		else {
			ss << namespaze << "::";
		}
		ss << il2cpp_functions::class_get_name(klass);

		//if (generics) {
		//	il2cpp_functions::class_is_generic(klass);
		//	auto* genClass = klass->generic_class;
		//	if (genClass) {
		//		GenericsToStringHelper(genClass, ss);
		//	}
		//}
		return ss.str();
	}

	const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<const Il2CppType*> argTypes) {
		if (klass == nullptr)
		{
			return nullptr;
		}

		//// Check Cache
		//auto innerPair = classesNamesTypesInnerPairType(methodName, argTypes);
		//auto key = std::pair<Il2CppClass*, classesNamesTypesInnerPairType>(klass, innerPair);
		//auto itr = classesNamesTypesToMethodsCache.find(key);
		//if (itr != classesNamesTypesToMethodsCache.end()) {
		//	return itr->second;
		//}

		void* myIter = nullptr;
		const MethodInfo* current;
		const MethodInfo* methodInfo = nullptr;
		// Does NOT automatically recurse through klass's parents
		while ((current = il2cpp_functions::class_get_methods(klass, &myIter))) {
			if ((methodName == current->name) && ParameterMatch(current, argTypes)) {
				methodInfo = current;
			}
		}
		if (!methodInfo && klass->parent && klass->parent != klass) {
			methodInfo = FindMethod(klass->parent, methodName, argTypes);
		}

		if (!methodInfo) {
			std::stringstream ss;
			ss << "could not find method " << methodName << "(";
			bool first = true;
			for (auto t : argTypes) {
				if (!first) ss << ", ";
				first = false;
				ss << TypeGetSimpleName(t);
			}

		}
		//classesNamesTypesToMethodsCache.insert({ key, methodInfo });
		return methodInfo;
	}

	const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<const Il2CppClass*> classFromes) {
		std::vector<const Il2CppType*> argTypes = ClassVecToTypes(classFromes);
		return FindMethod(klass, methodName, argTypes);
	}

	const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<std::string_view> argSpaceClass) {
		std::vector<const Il2CppType*> argTypes;
		for (int i = 0; i < argSpaceClass.size() - 1; i += 2) {
			auto clazz = GetClassFromName(argSpaceClass[i].data(), argSpaceClass[i + 1].data());
			argTypes.push_back(il2cpp_functions::class_get_type(clazz));
		}
		return FindMethod(klass, methodName, argTypes);
	}

	const MethodInfo* FindMethodFromArgsName(Il2CppClass* klass, std::string_view methodName, std::vector<std::string_view> argNames) {
		void* myIter = nullptr;
		const MethodInfo* current;
		const MethodInfo* methodInfo = nullptr;
		// Does NOT automatically recurse through klass's parents
		while ((current = il2cpp_functions::class_get_methods(klass, &myIter))) {
			if (methodName == current->name) {
				if (argNames.size() != il2cpp_functions::method_get_param_count(current))
					continue;
				methodInfo = current;
				for (size_t i = 0; i < argNames.size(); i++)
				{
					auto param_name = il2cpp_functions::method_get_param_name(current, i);
					if (argNames[i] != param_name)
					{
						methodInfo = nullptr;
						break;
					}
				}
			}
		}
		if (!methodInfo && klass->parent && klass->parent != klass) {
			methodInfo = FindMethodFromArgsName(klass->parent, methodName, argNames);
		}

		if (!methodInfo) {
			std::stringstream ss;
			ss << "could not find method " << methodName << "(";
			bool first = true;
			for (auto t : argNames) {
				if (!first) ss << ", ";
				first = false;
				ss << t;
			}
			LOG("ERROR: %s\n", ss.str().c_str());
		}
		return methodInfo;
	}



	const MethodInfo* FindMethodUnsafe(Il2CppClass* klass, std::string_view methodName, int argsCount) {
		if (klass == nullptr)
		{
			return nullptr;
		}

		//// Check Cache
		//auto innerPair = std::pair<std::string, decltype(MethodInfo::parameters_count)>(methodName, argsCount);
		//auto key = std::pair<Il2CppClass*, decltype(innerPair)>(klass, innerPair);
		//auto itr = classesNamesToMethodsCache.find(key);
		//if (itr != classesNamesToMethodsCache.end()) {
		//	return itr->second;
		//}
		// Recurses through klass's parents
		auto methodInfo = il2cpp_functions::class_get_method_from_name(klass, methodName.data(), argsCount);
		if (!methodInfo) {
			LOG("ERROR: could not find method %s with %i parameters in class '%s'!\n", methodName.data(), argsCount,
				ClassStandardName(klass, false).c_str());
			//LogMethods(klass, true);
		}
		//classesNamesToMethodsCache.insert({ key, methodInfo });
		return methodInfo;
	}

	const MethodInfo* FindMethodUnsafe(std::string_view nameSpace, std::string_view className, std::string_view methodName, int argsCount) {
		return FindMethodUnsafe(GetClassFromName(nameSpace.data(), className.data()), methodName, argsCount);
	}

	const MethodInfo* FindMethodUnsafe(Il2CppObject* instance, std::string_view methodName, int argsCount) {
		auto klass = il2cpp_functions::object_get_class(instance);
		if (klass == nullptr)
		{
			return nullptr;
		}
		return FindMethodUnsafe(klass, methodName, argsCount);
	}

	std::vector<const Il2CppType*> ClassVecToTypes(std::vector<const Il2CppClass*> seq) {
		std::vector<const Il2CppType*> types(seq.size());
		std::transform(seq.begin(), seq.end(), types.begin(), il2cpp_functions::class_get_type_const);
		return types;
	}

}

