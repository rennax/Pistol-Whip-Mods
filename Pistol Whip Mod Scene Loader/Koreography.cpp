#include "Koreography.hpp"
#include "List.hpp"
#include "TempoSectionDef.hpp"
#include "KoreographyTrackBase.hpp"

using namespace CSharp;

Koreography::Koreography()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo", "Koreography");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to construct koreography\n");
}

Koreography::Koreography(Il2CppObject* obj) : self(obj)
{
}

Koreography::~Koreography()
{
}

Il2CppObject* Koreography::Load(json j)
{
	return nullptr;
}

json Koreography::Dump()
{
	json j;
	
	List<Il2CppObject*> tempoSections(il2cpp_utils::GetFieldValue(self, "mTempoSections"));
	for (size_t i = 0; i < tempoSections.Count(); i++)
	{
		TempoSectionDef tempoSection(tempoSections[i]);
		j["mTempoSections"].push_back(tempoSection.Dump());
	}

	List<Il2CppObject*> mTracks(il2cpp_utils::GetFieldValue(self, "mTracks"));
	for (size_t i = 0; i < mTracks.Count(); i++)
	{
		KoreographyTrackBase trackBase(mTracks[i]);
		j["mTracks"].push_back(trackBase.Dump());
	}
	
	Il2CppString* audioPath = nullptr;
	il2cpp_utils::GetFieldValue(&audioPath, self, "mAudioFilePath");
	if (audioPath != nullptr)
		mAudioFilePath = to_utf8(csstrtostr(audioPath));
	j["mAudioFilePath"] = mAudioFilePath;

	il2cpp_utils::GetFieldValue(&mSampleRate, self, "mSampleRate");
	j["mSampleRate"] = mSampleRate;

	il2cpp_utils::GetFieldValue(&mIgnoreLatencyOffset, self, "mIgnoreLatencyOffset");
	j["mIgnoreLatencyOffset"] = mIgnoreLatencyOffset;

	Il2CppString* clipName_ = nullptr;
	il2cpp_utils::GetFieldValue(&clipName_, self, "clipName");
	if (clipName_ != nullptr)
		clipName = to_utf8(csstrtostr(clipName_));
	j["clipName"] = clipName;

	il2cpp_utils::GetFieldValue(&lastUpdateStart, self, "lastUpdateStart");
	j["lastUpdateStart"] = lastUpdateStart;

	il2cpp_utils::GetFieldValue(&lastUpdateEnd, self, "lastUpdateEnd");
	j["lastUpdateEnd"] = lastUpdateEnd;

	return j;
}
