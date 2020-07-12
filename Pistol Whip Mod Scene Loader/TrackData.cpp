#include "TrackData.hpp"
#include "BeatData.hpp"
#include "AssetBundle.hpp"


TrackData::TrackData()
{
	LOG("WARNING: Dont use TrackData default contructor\nIf you see this message the program most likely crashed\n");
}


TrackData::TrackData(Il2CppObject* levelData_, Il2CppObject* obj) 
	: levelData(levelData_), self(obj)
{}


TrackData::TrackData(Il2CppObject* levelData_) : levelData(levelData_)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "TrackData");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create TrackData object\n");
	else
		LOG("Created TrackData object\n");
}


Il2CppObject* TrackData::Load(json j)
{
	Il2CppObject* assetDB = AssetBundle::LoadFromFile("Custom Levels/x02/static_objects");

	//Create and assign koreography
	auto audioClipClass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
	auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(audioClipClass));
	Il2CppObject* audio = AssetBundle::LoadAsset(assetDB, "song.ogg", type);

	auto koreographyClass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo", "Koreography");
	koreography = il2cpp_functions::object_new(koreographyClass);
	if (!il2cpp_utils::RunMethod(koreography, ".ctor"))
		LOG("WARNING: Failed to construct Koreography in TrackData\n");

	if (!il2cpp_utils::SetFieldValue(self, "koreography", koreography))
		LOG("WARNING: Failed to assign koreography in TrackData\n");

	

	LoadBeatTimes(j["beatTimes"]);
	LoadBeats(j["beats"]);

	int diff = j["difficulty"]; // Hacky but whatever
	difficulty = static_cast<Difficulty>(diff);
	if (!il2cpp_utils::SetFieldValue(self, "difficulty", &difficulty))
		LOG("WARNING: Failed to assign difficulty in TrackData\n");

	playerSpeed = j["playerSpeed"];
	if (!il2cpp_utils::SetFieldValue(self, "playerSpeed", &playerSpeed))
		LOG("WARNING: Failed to assign playerSpeed in TrackData\n");

	return self;
}


void TrackData::LoadBeatTimes(json j)
{
	for (auto t : j)
	{
		beatTimesVec.push_back(t);
	}

	List<float> beatTimes(il2cpp_utils::GetFieldValue(self, "beatTimes"));
	for (auto t : beatTimesVec)
	{
		beatTimes.Add(t);
	}
}

void TrackData::LoadBeats(json j)
{
	List<Il2CppObject*> beatsList(il2cpp_utils::GetFieldValue(self, "beats"));
	for (auto b : j)
	{
		BeatData* beat = new BeatData(b["time"]);
		beatsList.Add(beat->Load(b));
		beats.push_back(beat);
	}
}

json TrackData::DumpToJson()
{
	json j;

	auto beats = GetBeats();
	for (size_t i = 0; i < beats.Count(); i++)
	{
		BeatData beat(beats[i]);
		j["beats"].push_back(beat.DumpToJson());
	}

	auto beatTimes = GetBeatTimes();
	for (size_t i = 0; i < beatTimes.Count(); i++)
	{
		j["beat_times"].push_back(beatTimes[i]);
	}

	j["difficulty"] = GetDifficulty();

	j["player_speed"] = GetPlayerSpeed();

	float songLength;
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "TrackData");
	il2cpp_utils::RunMethod(&songLength, self, il2cpp_utils::GetPropertyGetMethod(klass, "songLength"));
	j["song_length"] = songLength;

	float worldLength;
	il2cpp_utils::RunMethod(&worldLength, self, il2cpp_utils::GetPropertyGetMethod(klass, "worldLength"));
	j["world_length"] = songLength;

	return j;
}

CSharp::List<float> TrackData::GetBeatTimes()
{
	List<float> beatTimes(il2cpp_utils::GetFieldValue(self, "beatTimes"));
	return beatTimes;
}

CSharp::List<Il2CppObject*> TrackData::GetBeats()
{
	List<Il2CppObject*> beats(il2cpp_utils::GetFieldValue(self, "beats"));
	return beats;
}

float TrackData::GetPlayerSpeed()
{
	float playerSpeed = 3;
	il2cpp_utils::GetFieldValue(&playerSpeed, self, "playerSpeed");
	return playerSpeed;
}

int TrackData::GetDifficulty()
{
	int difficulty = 3;
	il2cpp_utils::GetFieldValue(&difficulty, self, "difficulty");
	return difficulty;
}