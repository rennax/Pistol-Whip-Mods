#ifndef ASSETBUNDLE_HPP
#define ASSETBUNDLE_HPP
#include "il2cpp_utils.hpp"

namespace AssetBundle {

	void Init();

	Il2CppObject* LoadFromFile(std::string_view path);


	Il2CppObject* LoadAsset(std::string_view bundlePath, std::string_view assetName);
	Il2CppObject* LoadAsset(Il2CppObject* bundle, std::string_view assetName);
	Il2CppObject* LoadAsset(Il2CppObject* bundle, std::string_view assetName, Il2CppObject* type);

	bool Contains(Il2CppObject* bundle, std::string_view assetName);


};


#endif // !ASSETBUNDLE_HPP
