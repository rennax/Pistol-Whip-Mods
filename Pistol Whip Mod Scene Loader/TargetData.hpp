#ifndef TARGETDATA_HPP
#define TARGETDATA_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "WorldObject.hpp"

using json = nlohmann::json;

enum class CheevoID : int32_t {
	NONE = 0,
	Dancer = 1,
	Replicant = 2,
	Bridge = 3,
	MAX = 4,
	Any = 2147483647,
};

class TargetData
{
	enum class Distance : int32_t {
		Near = 0,
		Middle = 1,
		Far = 2
	};
public:
	TargetData();
	TargetData(Il2CppObject* obj);
	~TargetData();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self = nullptr;
	Distance distance = Distance::Near;
	Il2CppObject* enemySequence = nullptr;
	WorldPoint enemyOffset;
	bool ignoreForLevelRank = false;
	Array<float>* fireTimes = nullptr;
	CheevoID cheevoID = CheevoID::NONE;
	bool noGround = false;
};

#endif // !TARGETDATA_HPP


