#ifndef ENEMYSEQUENCE_HPP
#define ENEMYSEQUENCE_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include "TargetData.hpp"
#include "List.hpp"

using namespace CSharp;
using json = nlohmann::json;

enum class EnemyToughness : int32_t {
	Normal = 0,
	Tough = 1,
	ChuckNorris = 2,
	Bazooka = 3,
	Minigun = 4,
	Shield = 5
};

struct EnemyType {
	EnemyToughness toughness;
};

class EnemySequence
{
public:
	EnemySequence();
	EnemySequence(Il2CppObject* obj);
	~EnemySequence();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self;
	EnemyType enemyType; //EnemyType
	Il2CppObject* actionHolder; //GameObject
	CheevoID forceCheevoID;
	//List<EnemyAction> actions; // We cant default create lists so we just grap it from self when we need to
	float playerActionLerp;
	WorldPoint localActionPoint;
	bool autospawn;
	int32_t actionIndex;
	Il2CppObject* OnSequenceStart; //Action
	Il2CppObject* OnSequenceStop; //Action
	bool isThreat;
	float duration;
	Il2CppObject* actor; //Enemy
};



#endif // !ENEMYSEQUENCE_HPP
