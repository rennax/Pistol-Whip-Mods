#ifndef BEATDATA_HPP
#define BEATDATA_HPP
#include "il2cpp_utils.hpp"
#include "List.hpp"
#include <string_view>
#include "json.hpp"

using json = nlohmann::json;



class BeatData {
public:
	BeatData(float time);
	BeatData(Il2CppObject* obj);
	CSharp::List<Il2CppObject*> GetTargets();
	CSharp::List<Il2CppObject*> GetObstacles();
	float GetTime();
	void Load(std::string_view path);
	json DumpToJson();
private:
	Il2CppObject* beatData;
};

#endif // !BEATDATA_HPP
