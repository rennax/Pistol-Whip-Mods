#ifndef BEATDATA_HPP
#define BEATDATA_HPP
#include "il2cpp_utils.hpp"
#include "List.hpp"
#include "json.hpp"
#include "TargetData.hpp"
#include "ObstacleData.hpp"
#include <vector>

using json = nlohmann::json;

class BeatData {
public:
	BeatData(float time_);
	BeatData(Il2CppObject* obj);
	CSharp::List<Il2CppObject*> GetTargets();
	CSharp::List<Il2CppObject*> GetObstacles();
	float GetTime();
	Il2CppObject* Load(json j);
	json DumpToJson();
private:
	Il2CppObject* self;
	float time = 0;
	std::vector<ObstacleData*> obstacles;
};

#endif // !BEATDATA_HPP
