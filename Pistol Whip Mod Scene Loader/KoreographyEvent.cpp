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
	int32_t mStartSample = j["mStartSample"], mEndSample = j["mEndSample"];
	
	if (j["mPayload"] == 0)
	{
		void* mPayload = nullptr;
		il2cpp_utils::SetFieldValue(self, "mPayload", mPayload);
	}
	il2cpp_utils::SetFieldValue(self, "mStartSample", &mStartSample);
	il2cpp_utils::SetFieldValue(self, "mEndSample", &mEndSample);
	return self;
}

json KoreographyEvent::Dump()
{
	json j;
	
	il2cpp_utils::GetFieldValue(&mStartSample, self, "mStartSample");
	j["mStartSample"] = mStartSample;

	il2cpp_utils::GetFieldValue(&mEndSample, self, "mEndSample");
	j["mEndSample"] = mEndSample;

	mPayload = il2cpp_utils::GetFieldValue(self, "mPayload");
	if (mPayload != nullptr)
	{
		Il2CppClass* klass = il2cpp_functions::object_get_class(mPayload);
		j["mPayload"] = il2cpp_functions::class_get_name(klass);
	}
	else
	{
		j["mPayload"] = 0;
	}

	return j;
}
