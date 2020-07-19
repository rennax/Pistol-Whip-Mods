#include "WwiseKoreographySet.hpp"
#include "List.hpp"
#include "utils-functions.hpp"
#include "WwiseKoreoMediaIDEntry.hpp"

using namespace CSharp;

WwiseKoreographySet::WwiseKoreographySet(Il2CppObject* koreo_) : koreo(koreo_)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo.Players.Wwise", "WwiseKoreographySet");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create WwiseKoreographySet\n");
}

WwiseKoreographySet::WwiseKoreographySet(Il2CppObject* koreo_, Il2CppObject* obj)
	: koreo(koreo_), self(obj)
{
}

WwiseKoreographySet::~WwiseKoreographySet()
{
}

Il2CppObject* WwiseKoreographySet::Load(json j)
{
	List<Il2CppObject*> koreographies(il2cpp_utils::GetFieldValue(self, "koreographies"));
	for (auto ent : j)
	{
		WwiseKoreoMediaIDEntry entry;
		koreographies.Add(entry.Load(ent, koreo));
	}
	return self;
}

json WwiseKoreographySet::Dump()
{
	json j;
	List<Il2CppObject*> koreographies(il2cpp_utils::GetFieldValue(self, "koreographies"));
	for (size_t i = 0; i < koreographies.Count(); i++)
	{
		json t;
		uint64_t mediaID = UINT64_MAX; // Makes sure we can see if we failed to set value
		il2cpp_utils::GetFieldValue(&mediaID, koreographies[i], "mediaID");
		
		std::string clipName;
		Il2CppString* cn = nullptr;
		il2cpp_utils::GetFieldValue(cn, koreo, "clipName");
		clipName = to_utf8(csstrtostr(cn));


		t["mediaID"] = mediaID;
		t["clipName"] = clipName;
		j["koreographies"].push_back(t);
	}
	return j;
}
