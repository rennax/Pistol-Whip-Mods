#ifndef OBSTACLEDATA_HPP
#define OBSTACLEDATA_HPP

#include "List.hpp"
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


class ObstacleData
{
public:
	enum class Placement : int {
		EvenMoreLeft = -3,
		FarLeft = -2,
		Left = -1,
		Center = 0,
		Right = 1,
		FarRight = 2,
		EvenMoreRight = 3
	};
	enum class ObstacleType : int {
		Sidestep = 0,
		LimboTall = 1,
		LimboShort = 2,
	};
	ObstacleData();
	ObstacleData(Il2CppObject* obj);
	~ObstacleData();
	Il2CppObject* Load(json j);
private:
	Placement placement = Placement::Center;
	ObstacleType type = ObstacleType::LimboTall;
	Il2CppObject* self = nullptr;
};


#endif // !OBSTACLEDATA_HPP
