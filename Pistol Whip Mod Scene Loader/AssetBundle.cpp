#include "AssetBundle.hpp"

namespace AssetBundle {

	static bool initialized = false;

	static Il2CppObject* (*LoadFromFile_Internal)(Il2CppString*, int32_t, int64_t);
	typedef Il2CppObject* (*LoadFromFile_Internal_t)(Il2CppString*, int32_t, int64_t);

	static Il2CppObject* (*LoadAsset_Internal)(void* self, Il2CppString* name, Il2CppObject* type);
	typedef Il2CppObject* (*LoadAsset_Internal_t)(void* self, Il2CppString* name, Il2CppObject* type);

	static Il2CppObject* (*Contains_Internal)(void* self, Il2CppString* name);
	typedef Il2CppObject* (*Contains_Internal_t)(void* self, Il2CppString* name);

	void Init()
	{
		if (!initialized)
		{
			LoadFromFile_Internal = (LoadFromFile_Internal_t)il2cpp_functions::resolve_icall("UnityEngine.AssetBundle::LoadFromFile_Internal(System.String, System.UInt32, System.UInt64)");
			LoadAsset_Internal = (LoadAsset_Internal_t)il2cpp_functions::resolve_icall("UnityEngine.AssetBundle::LoadAsset_Internal(System.String)");
			Contains_Internal = (Contains_Internal_t)il2cpp_functions::resolve_icall("UnityEngine.AssetBundle::Contains(System.String)");
			initialized = true;
		}
	}

	Il2CppObject* LoadFromFile(Il2CppString* path) {
		return LoadFromFile_Internal(path, 0, 0);
	}


	Il2CppObject* LoadAsset(std::string_view bundlePath, std::string_view assetName) {
		Il2CppObject* bundle = LoadFromFile(il2cpp_utils::createcsstr(bundlePath));
		if (bundle == nullptr)
		{
			LOG("WARNING: AssetBundle::LoadAsset: Failed to load AssetBundle from path %s\n", bundlePath.data());
			return nullptr;
		}

		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Object");
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

		return LoadAsset_Internal(bundle, il2cpp_utils::createcsstr(assetName), type);
	}


	Il2CppObject* LoadAsset(Il2CppObject* bundle, std::string_view assetName) {
		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Object");
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

		return LoadAsset_Internal(bundle, il2cpp_utils::createcsstr(assetName), type);
	}

	bool Contains(Il2CppObject* bundle, std::string_view assetName) {
		return Contains_Internal(bundle, il2cpp_utils::createcsstr(assetName));
	}


};
