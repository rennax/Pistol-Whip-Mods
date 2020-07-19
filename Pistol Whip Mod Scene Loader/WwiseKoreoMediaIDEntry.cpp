#include "WwiseKoreoMediaIDEntry.hpp"


WwiseKoreoMediaIDEntry::WwiseKoreoMediaIDEntry()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo.Players.Wwise", "WwiseKoreographySet");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create WwiseKoreoMediaIDEntry\n");
}

WwiseKoreoMediaIDEntry::~WwiseKoreoMediaIDEntry()
{
}

Il2CppObject* WwiseKoreoMediaIDEntry::Load(json j, Il2CppObject* koreo)
{
	il2cpp_utils::SetFieldValue(self, "koreo", koreo);
	mediaID = j["mediaID"];
	il2cpp_utils::SetFieldValue(self, "mediaID", &mediaID);
	return self;
}
