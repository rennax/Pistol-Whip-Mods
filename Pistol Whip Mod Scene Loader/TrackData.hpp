#ifndef TRACKDATA_HPP
#define TRACKDATA_HPP
#include "List.hpp"
#include "il2cpp_utils.hpp"
#include <string_view>
#include "json.hpp"
#include <vector>
#include "BeatData.hpp"
#include "TargetData.hpp"

using json = nlohmann::json;

using namespace CSharp;


enum class Difficulty : int {
	Easy = 0,
	Normal = 1,
	Hard = 2,
	Expert = 3
};

class TrackData {
public:
	TrackData();
	TrackData(Il2CppObject* levelData_, Il2CppObject* obj);
	TrackData(Il2CppObject* levelData_);
	TrackData(Il2CppObject* levelData_, bool dontToShit);
	Il2CppObject* Load(json j);
	inline Il2CppObject* GetTrackData() { return self; }
	json DumpToJson();
private:
	void LoadBeatTimes(json j);
	void LoadBeats(json j);

	CSharp::List<float> GetBeatTimes();
	CSharp::List<Il2CppObject*> GetBeats();
	float GetPlayerSpeed();
	int GetDifficulty();
private:
	Il2CppObject* self = nullptr;
	Il2CppObject* levelData = nullptr;
	Difficulty difficulty = Difficulty::Easy;
	Il2CppObject* koreography = nullptr;
	float playerSpeed = 3;
	std::vector<float> beatTimesVec;
	std::vector<BeatData*> beats;
};


#endif // !TRACKDATA_HPP
