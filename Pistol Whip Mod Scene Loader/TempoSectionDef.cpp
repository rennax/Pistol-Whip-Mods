#include "TempoSectionDef.hpp"

TempoSectionDef::TempoSectionDef()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo","TempoSectionDef");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create TempoSectionDef\n");
}

TempoSectionDef::~TempoSectionDef()
{
}

Il2CppObject* TempoSectionDef::Load(json j)
{
	sectionName = j["sectionName"];
	startSample = j["startSample"];
	samplesPerBeat = j["samplesPerBeat"];
	beatsPerMeasure = j["beatsPerMeasure"];
	bStartNewMeasure = j["bStartNewMeasure"];

	Il2CppString* str = il2cpp_utils::createcsstr(sectionName);
	il2cpp_utils::SetFieldValue(self, "sectionName", str);
	il2cpp_utils::SetFieldValue(self, "startSample", &startSample);
	il2cpp_utils::SetFieldValue(self, "samplesPerBeat", &samplesPerBeat);
	il2cpp_utils::SetFieldValue(self, "beatsPerMeasure", &beatsPerMeasure);
	il2cpp_utils::SetFieldValue(self, "bStartNewMeasure", &bStartNewMeasure);
	return self;
}

json TempoSectionDef::Dump()
{
	json j;

	Il2CppString* str = nullptr;
	il2cpp_utils::GetFieldValue(str, self, "sectionName");
	il2cpp_utils::GetFieldValue(&startSample, self, "startSample");
	il2cpp_utils::GetFieldValue(&samplesPerBeat, self, "samplesPerBeat");
	il2cpp_utils::GetFieldValue(&beatsPerMeasure, self, "beatsPerMeasure");
	il2cpp_utils::GetFieldValue(&bStartNewMeasure, self, "bStartNewMeasure");

	j["sectionName"] = to_utf8(csstrtostr(str));
	j["startSample"] = startSample;
	j["samplesPerBeat"] = samplesPerBeat;
	j["beatsPerMeasure"] = beatsPerMeasure;
	j["bStartNewMeasure"] = bStartNewMeasure;
	return j;
}
