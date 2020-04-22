#include "TrackData.hpp"
#include "BeatData.hpp"

TrackData::TrackData()
{
	auto klass = il2cpp_utils::GetClassFromName("", "TrackData");
	trackData = il2cpp_functions::object_new(klass);
	il2cpp_utils::RunMethod(trackData, ".ctor");
}

TrackData::TrackData(Il2CppObject* obj) : trackData(obj)
{
	
}

CSharp::List<float> TrackData::GetBeatTimes()
{
	List<float> beatTimes(il2cpp_utils::GetFieldValue(trackData, "beatTimes"));
	return beatTimes;
}

CSharp::List<Il2CppObject*> TrackData::GetBeats()
{
	List<Il2CppObject*> beats(il2cpp_utils::GetFieldValue(trackData, "beats"));
	return beats;
}

float TrackData::GetPlayerSpeed()
{
	float playerSpeed = 3;
	il2cpp_utils::GetFieldValue(&playerSpeed, trackData, "playerSpeed");
	return playerSpeed;
}

int TrackData::GetDifficulty()
{
	int difficulty = 3;
	il2cpp_utils::GetFieldValue(&difficulty, trackData, "difficulty");
	return difficulty;
}

void TrackData::Load(std::string_view file)
{

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
	il2cpp_utils::RunMethod(&songLength, trackData, il2cpp_utils::GetPropertyGetMethod(klass, "songLength"));
	j["song_length"] = songLength;

	float worldLength;
	il2cpp_utils::RunMethod(&worldLength, trackData, il2cpp_utils::GetPropertyGetMethod(klass, "worldLength"));
	j["world_length"] = songLength;

	return j;
}
