#include "Koreography.hpp"
#include "List.hpp"
#include "TempoSectionDef.hpp"
#include "KoreographyTrackBase.hpp"
#include "AssetBundle.hpp"

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


	mSampleRate = j["mSampleRate"];
	lastUpdateEnd = j["lastUpdateEnd"];
	lastUpdateStart = j["lastUpdateStart"];
	mIgnoreLatencyOffset = j["mIgnoreLatencyOffset"];
	clipName = j["clipName"];
	mAudioFilePath = j["mAudioFilePath"];

	List<Il2CppObject*> mTempoSections(il2cpp_utils::GetFieldValue(self, "mTempoSections"));
	for (auto section : j["mTempoSections"])
	{
		TempoSectionDef sec;
		mTempoSections.Add(sec.Load(section));
	}

	List<Il2CppObject*> mTracks(il2cpp_utils::GetFieldValue(self, "mTracks"));
	for (auto b : j["mTracks"])
	{
		KoreographyTrackBase base;
		mTracks.Add(base.Load(b));
	}

	il2cpp_utils::SetFieldValue(self, "mSampleRate", &mSampleRate);
	il2cpp_utils::SetFieldValue(self, "lastUpdateEnd", &lastUpdateEnd);
	il2cpp_utils::SetFieldValue(self, "lastUpdateStart", &lastUpdateStart);
	il2cpp_utils::SetFieldValue(self, "mIgnoreLatencyOffset", &mIgnoreLatencyOffset);
	il2cpp_utils::SetFieldValue(self, "mAudioFilePath", il2cpp_utils::createcsstr(mAudioFilePath.c_str()));
	il2cpp_utils::SetFieldValue(self, "clipName", il2cpp_utils::createcsstr(clipName.c_str()));

	//Il2CppObject* assetDB = AssetBundle::LoadFromFile("Custom Levels/x02/song");
	//auto audioClipClass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
	//auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(audioClipClass));
	//Il2CppObject* audio = AssetBundle::LoadAsset(assetDB, "Burn You Tonight.ogg", type);

	//if (!il2cpp_utils::RunMethod(self, "set_SourceClip", audio))
	//	LOG("WARNING: Failed to call Koreography::set_SourceClip(audioClip) in TrackData");

	return self;
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
