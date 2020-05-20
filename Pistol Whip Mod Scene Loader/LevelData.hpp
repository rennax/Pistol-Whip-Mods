#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "WorldObject.hpp"

using json = nlohmann::json;


class LevelData
{
public:
	LevelData(Il2CppObject* obj);
	LevelData();
	~LevelData();
	json Dump();
	Il2CppObject* Load(json j);
private:
	void LoadWorldObjects(json j);
private:
	std::vector<WorldObject> worldObjects;
	Il2CppObject* self;
};

#endif // !LEVELDATA_HPP
