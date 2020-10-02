#include "TrackData.hpp"
#include "BeatData.hpp"
#include "AssetBundle.hpp"
#include "GameObject.hpp"
#include "Koreography.hpp"

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

TrackData::TrackData(Il2CppObject* levelData_, bool dontToShit) : levelData(levelData_)
{
	Il2CppObject* obj = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
	GameObject::SetName(obj, "Test_easy");
	GameObject::AddComponent(obj, il2cpp_utils::GetClassFromName("", "TrackData"));

	auto klass = il2cpp_utils::GetClassFromName("", "TrackData");
	auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));
	il2cpp_utils::RunMethod(&self, obj, "GetComponent", type);
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to create TrackData object\n");
	else
		LOG("Created TrackData object\n");


}


Il2CppObject* TrackData::Load(json j)
{
	Il2CppObject* assetDB = AssetBundle::LoadFromFile("Custom Levels/x02/song");

	//Create and assign koreography
	auto audioClipClass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
	int length = 1, channels = 2, frequency = 1;
	bool stream = false;
	auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(audioClipClass));
	Il2CppObject* audio = nullptr;
	il2cpp_utils::RunMethod(
		&audio,
		audioClipClass,
		"Create",
		il2cpp_utils::createcsstr(j["songName"].get<std::string>()),
		&length,
		&channels,
		&frequency,
		&stream
	);


	//auto audioClipClass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
	//auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(audioClipClass));
	//Il2CppObject* audio = AssetBundle::LoadAsset(assetDB, j["songName"].get<std::string>() + ".ogg", type);


	//auto koreographyClass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo", "Koreography");
	//koreography = il2cpp_functions::object_new(koreographyClass);
	//if (!il2cpp_utils::RunMethod(koreography, ".ctor"))
	//	LOG("WARNING: Failed to construct Koreography in TrackData\n");



	Koreography koreography;
	Il2CppObject* koreo = koreography.Load(j["koreography"]);
	if (!il2cpp_utils::SetFieldValue(self, "koreography", koreo))
		LOG("WARNING: Failed to assign koreography in TrackData\n");

	if (!il2cpp_utils::RunMethod(koreo, "set_SourceClip", audio))
		LOG("WARNING: Failed to call Koreography::set_SourceClip(audioClip) in TrackData");

	LoadBeatTimes(j["beatTimes"]);
	LoadBeats(j["beats"]);

	int diff = j["difficulty"]; // Hacky but whatever
	difficulty = static_cast<Difficulty>(diff);
	if (!il2cpp_utils::SetFieldValue(self, "difficulty", &difficulty))
		LOG("WARNING: Failed to assign difficulty in TrackData\n");


	auto nameProp = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("", "TrackData"), "name");
	std::string name = j["songName"].get<std::string>();
	if (diff == 0)
		name += "_Easy";
	else if (diff == 1)
		name += "_Normal";
	else if (diff == 2)
		name += "_Hard";
	else if (diff == 3)
		name += "_Expert";
	
	il2cpp_utils::RunMethod(self, nameProp, il2cpp_utils::createcsstr(name));

	playerSpeed = j["playerSpeed"];
	if (!il2cpp_utils::SetFieldValue(self, "playerSpeed", &playerSpeed))
		LOG("WARNING: Failed to assign playerSpeed in TrackData\n");

	if (!il2cpp_utils::SetFieldValue(self, "level", levelData))
		LOG("WARNING: Failed to assign level in TrackData\n");

	Il2CppObject* musicMap;
	il2cpp_utils::RunMethod(&musicMap, il2cpp_utils::GetClassFromName("CloudheadGames.PistolWhip.MusicMapperSystem", "MusicMap"), "op_Implicit", koreo);
	il2cpp_utils::SetFieldValue(self, "musicMap", musicMap);

	sampleRate = j["sampleRate"];
	if (!il2cpp_utils::SetFieldValue(self, "sampleRate", &sampleRate))
		LOG("WARNING: Failed to assign sampleRate in TrackData\n");

	return self;
}


void TrackData::LoadBeatTimes(json j)
{
	List<float> beatTimes(il2cpp_utils::GetFieldValue(self, "beatTimes"));
	for (size_t i = 0; i < j.size(); i++)
	{
		float beatTime = j.at(i);
		beatTimes.Add(beatTime);
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