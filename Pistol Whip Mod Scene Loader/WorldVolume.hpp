#ifndef WORLDVOLUME_HPP
#define WORLDVOLUME_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

enum class GeoVolume : int32_t {
	Subtractive = 0,
	Additive = 1
};

class WorldVolume
{
public:
	WorldVolume();
	~WorldVolume();
	Il2CppObject* Load(json j);

private:
	Il2CppObject* self;
	Vector3i position;
	Vector3i min;
	Vector3i max;
	Vector3i size;
	GeoVolume type;
};

#endif // !WORLDVOLUME_HPP
