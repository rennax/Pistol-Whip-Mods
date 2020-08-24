#ifndef WORLDREGION_HPP
#define WORLDREGION_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


enum class Region : int32_t {
	Open = 0,
	Closed = 1
};

class WorldRegion
{
public:
	WorldRegion(Region type);
	WorldRegion(Il2CppObject* obj);
	~WorldRegion();
	json Dump();
	Il2CppObject* Load(json j);
private:
	Vector3i position;
	Vector3i min;
	Vector3i max;
	Region type;
	Il2CppObject* self;
};

#endif // !WORLDREGION_HPP
