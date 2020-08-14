#ifndef ENEMYACTION_HPP
#define ENEMYACTION_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

enum class ActorAction : int32_t {
	Wait = 0,
	Move = 1,
	AimStart = 2,
	AimStop = 3,
	Fire = 4,
	AimAndFire = 5,
	Crouch = 6,
	Stand = 7,
	Slide = 8,
	Roll = 9,
	Vault = 10,
	StandingCoverIdle = 11,
	MeleeKick = 12,
	PopOut = 13,
	HideStanding = 14,
	StopFiring = 15,
	Guard = 16,
	Dance_01 = 17,
	Dance_02 = 18,
	Fly = 19,
	AirshipPilot = 20
};

enum class EnemyActionType : int32_t {
	Wait = 0,
	Move = 1,
	AimStart = 2,
	AimStop = 3,
	Fire = 4,
	AimAndFire = 5,
	Instant = 6,
	RootMotion = 7,
	StopFiring = 8
};

class EnemyAction
{
public:
	EnemyAction(Il2CppObject* enemySequence);
	EnemyAction(Il2CppObject* enemySequence, Il2CppObject* obj);
	~EnemyAction();
	Il2CppObject* Load(json j);
	json Dump();
private:
	void LoadWait(json j);
	void LoadMove(json j);
	void LoadAimStart(json j);
	void LoadAimStop(json j);
	void LoadFire(json j);
	void LoadAimAndFire(json j);
	void LoadInstant(json j);
	void LoadRootMotion(json j);
	void LoadStopFiring(json j);
private:
	Il2CppObject* self = nullptr;
	EnemyActionType type;
	Il2CppObject* sequence = nullptr;

public:
	enum class MoveSpeed : int32_t {
		Walk = 0,
		Run = 1,
	};
	enum class MoveFacing : int32_t {
		Forward = 0,
		Player = 1,
		Custom = 2,
	};
};



#endif // !ENEMYACTION_HPP
