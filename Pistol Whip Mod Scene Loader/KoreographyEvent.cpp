#include "KoreographyEvent.hpp"

KoreographyEvent::KoreographyEvent()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo", "KoreographyEvent");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to construct KoreographyEvent\n");
}

KoreographyEvent::KoreographyEvent(Il2CppObject* obj) : self(obj)
{
}

KoreographyEvent::~KoreographyEvent()
{
}

Il2CppObject* KoreographyEvent::Load(json j)
{
	return nullptr;
}

json KoreographyEvent::Dump()
{
	json j;
	
	il2cpp_utils::GetFieldValue(&mStartSample, self, "mStartSample");
	j["mStartSample"] = mStartSample;

	il2cpp_utils::GetFieldValue(&mEndSample, self, "mEndSample");
	j["mEndSample"] = mEndSample;
	return j;
}
