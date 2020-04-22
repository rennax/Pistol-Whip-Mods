#ifndef TRACKDATA_HPP
#define TRACKDATA_HPP
#include "List.hpp"
#include "il2cpp_utils.hpp"
#include <string_view>
#include "json.hpp"

using json = nlohmann::json;

using namespace CSharp;
class TrackData {
public:
	TrackData();
	TrackData(Il2CppObject* obj);
	CSharp::List<float> GetBeatTimes();
	CSharp::List<Il2CppObject*> GetBeats();
	float GetPlayerSpeed();
	int GetDifficulty();
	void Load(std::string_view file);
	inline Il2CppObject* GetTrackData() { return trackData; }
	json DumpToJson();
private:
	Il2CppObject* trackData = nullptr;
};


#endif // !TRACKDATA_HPP
