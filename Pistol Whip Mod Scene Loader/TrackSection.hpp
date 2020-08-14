#ifndef TRACKSECTION_HPP
#define TRACKSECTION_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


enum class Block : int32_t
{
	Unknown = 0,
	Air = 1,
	Solid = 2,
};

struct Debris
{
	enum class Distribution : int32_t
	{
		Ground = 0,
		PlayerLevel = 1,
		Projected = 2,
	};

	enum class Projection : int32_t
	{
		Down = 0,
		Outward = 1,
		Forward = 2,
		Up = 3,
	};

	enum class Spread : int32_t
	{
		Random = 0,
		Spread = 1,
	};

	enum class Shape : int32_t
	{
		Cube = 0,
		Pile = 1,
	};

	enum class Timing : int32_t
	{
		Normal = 0,
		AfterRegions = 1,
	};

	int32_t seed; // 0x0
	Distribution distribution; // 0x4
	Projection projection; // 0x8
	Spread spread; // 0xC
	float density; // 0x10
	Vector2i interval; // 0x14
	float uniformity; // 0x1C
	Vector3i minSize; // 0x20
	Vector3i maxSize; // 0x2C
	Shape shape; // 0x38
	bool buildOnAir; // 0x3C
	Timing timing; // 0x40
};
void to_json(json& j, const Debris& d);
void from_json(const json& j, Debris& d);

class TrackSection
{
public:
	TrackSection();
	TrackSection(Il2CppObject* obj);
	~TrackSection();
	Il2CppObject* Load(json j);
	json Dump();
private:
	void LoadFilledSection(json j);
private:
	Il2CppObject* self;
	float colorHue; // 0x10
	float colorSaturation; // 0x14
	float colorValue; // 0x18
	float fogHue; // 0x1C
	float fogSaturation; // 0x20
	float fogValue; // 0x24
	float glowHue; // 0x28
	float glowSaturation; // 0x2C
	float glowValue; // 0x30
	float enemyHue; // 0x34
	float enemySaturation; // 0x38
	float enemyValue; // 0x3C
	bool _customColors; // 0x40
	bool _customEnemyColor; // 0x41
	bool startingWall; // 0x42
	bool endingWall; // 0x43
	int32_t height; // 0x44
	int32_t groundHeight; // 0x48
	int32_t seed; // 0x4C
	int32_t start; // 0x50
	int32_t end; // 0x54
	Vector3i min; // 0x58
	Vector3i max; // 0x64
	Vector3i extent; // 0x70
	bool generateDebris; // 0x7C
	Debris debris; // 0x80
	int32_t propSeed; // 0xC4
	int32_t yStep; // 0xC8
	int32_t zStep; // 0xCC
	Array<int32_t>* yOffsets; // 0xD0
	Array<int32_t>* zOffsets; // 0xD8
	Array<int32_t>* blocks; // 0xE0
	Vector3i size; // 0xE8
	Il2CppObject* emptyBlocks; // 0xF8 HashSet<Vector3i>
	Il2CppObject* decorationBlocks; // 0x100 HashSet<Vector3i>
	Il2CppObject* props; // 0x108 List<WorldObject>
	Vector3i lastDebrisPoint; // 0x110
};

#endif // !TRACKSECTION_HPP
