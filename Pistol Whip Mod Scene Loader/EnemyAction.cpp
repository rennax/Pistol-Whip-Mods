#include "EnemyAction.hpp"
#include "WorldObject.hpp"

EnemyAction::EnemyAction(Il2CppObject* _enemySequence) : sequence(_enemySequence)
{
}

EnemyAction::EnemyAction(Il2CppObject* _enemySequence, Il2CppObject* obj) : sequence(_enemySequence), self(obj)
{
}

EnemyAction::~EnemyAction()
{
}

Il2CppObject* EnemyAction::Load(json j)
{
	//NOTE: Create and load data specific for the derived class
	type = static_cast<EnemyActionType>(j["type"]);
	switch (type)
	{
	case EnemyActionType::Wait:
		LoadWait(j);
		break;
	case EnemyActionType::Move:
		LoadMove(j);
		break;
	case EnemyActionType::AimStart:
		LoadAimStart(j);
		break;
	case EnemyActionType::AimStop:
		LoadAimStop(j);
		break;
	case EnemyActionType::Fire:
		LoadFire(j);
		break;
	case EnemyActionType::AimAndFire:
		LoadAimAndFire(j);
		break;
	case EnemyActionType::Instant:
		LoadInstant(j);
		break;
	case EnemyActionType::RootMotion:
		LoadRootMotion(j);
		break;
	case EnemyActionType::StopFiring:
		LoadStopFiring(j);
		break;
	default:
		break;
	}

	float duration = j["duration"];
	il2cpp_utils::SetFieldValue(self, "duration", &duration);

	//Do we need to only define the local, world or both points?
	WorldPoint localStartingPoint{j["localStartingPoint"]["position"], j["localStartingPoint"]["rotation"]};
	il2cpp_utils::SetFieldValue(self, "localStartingPoint", &localStartingPoint);

	WorldPoint localEndingPoint{ j["localEndingPoint"]["position"], j["localEndingPoint"]["rotation"] };
	il2cpp_utils::SetFieldValue(self, "localEndingPoint", &localEndingPoint);

	WorldPoint worldStartingPoint{ j["worldStartingPoint"]["position"], j["worldStartingPoint"]["rotation"] };
	il2cpp_utils::SetFieldValue(self, "worldStartingPoint", &worldStartingPoint);

	WorldPoint worldEndingPoint{ j["worldEndingPoint"]["position"], j["worldEndingPoint"]["rotation"] };
	il2cpp_utils::SetFieldValue(self, "worldEndingPoint", &worldEndingPoint);

	float sequenceStartTime = j["sequenceStartTime"];
	il2cpp_utils::SetFieldValue(self, "sequenceStartTime", &sequenceStartTime);

	il2cpp_utils::SetFieldValue(self, "sequence", sequence);

	float startTime = j["startTime"];
	il2cpp_utils::RunMethod(self, "set_startTime", &startTime);

	float endTime = j["endTime"];
	il2cpp_utils::RunMethod(self, "set_endTime", &endTime);

	return self;
}

json EnemyAction::Dump()
{
	LOG("TODO EnemyAction::Dump()\n");
	return json();
}

void EnemyAction::LoadWait(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionWait"));
	il2cpp_utils::RunMethod(self, ".ctor");

	float waitTime = j["waitTime"];
	il2cpp_utils::SetFieldValue(self, "waitTime", &waitTime);
}

void EnemyAction::LoadMove(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionMove"));
	il2cpp_utils::RunMethod(self, ".ctor");

	WorldPoint destination{ j["destination"]["position"] ,j["destination"]["rotation"] };
	il2cpp_utils::SetFieldValue(self, "destination", &destination);

	MoveSpeed speed = static_cast<MoveSpeed>(j["speed"]);
	il2cpp_utils::SetFieldValue(self, "speed", &speed);

	MoveFacing facing = static_cast<MoveFacing>(j["facing"]);
	il2cpp_utils::SetFieldValue(self, "facing", &facing);
}

void EnemyAction::LoadAimStart(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionAimStart"));
	il2cpp_utils::RunMethod(self, ".ctor");
}

void EnemyAction::LoadAimStop(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionAimStop"));
	il2cpp_utils::RunMethod(self, ".ctor");

	bool stopFacing = j["stopFacing"];
	il2cpp_utils::SetFieldValue(self, "stopFacing", &stopFacing);

	bool stopLooking = j["stopLooking"];
	il2cpp_utils::SetFieldValue(self, "stopLooking", &stopLooking);
}

void EnemyAction::LoadFire(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionFire"));
	il2cpp_utils::RunMethod(self, ".ctor");
}

void EnemyAction::LoadAimAndFire(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionAimAndFire"));
	il2cpp_utils::RunMethod(self, ".ctor");

	float actionDuration = j["actionDuration"];
	il2cpp_utils::SetFieldValue(self, "actionDuration", &actionDuration);

	bool stopFacingOnExit = j["stopFacingOnExit"];
	il2cpp_utils::SetFieldValue(self, "stopFacingOnExit", &stopFacingOnExit);

	bool stopLookingOnExit = j["stopLookingOnExit"];
	il2cpp_utils::SetFieldValue(self, "stopLookingOnExit", &stopLookingOnExit);

	float fireTime = j["fireTime"];
	il2cpp_utils::SetFieldValue(self, "fireTime", &fireTime);

	bool fired = j["fired"];
	il2cpp_utils::SetFieldValue(self, "fired", &fired);
}

void EnemyAction::LoadInstant(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionInstant"));
	il2cpp_utils::RunMethod(self, ".ctor");

	int32_t triggerHash = j["triggerHash"];
	il2cpp_utils::SetFieldValue(self, "triggerHash", &triggerHash);

	ActorAction action = static_cast<ActorAction>(j["action"]);
	il2cpp_utils::SetFieldValue(self, "action", &action);
}

void EnemyAction::LoadRootMotion(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionRootMotion"));
	il2cpp_utils::RunMethod(self, ".ctor");

	int32_t triggerHash = j["triggerHash"];
	il2cpp_utils::SetFieldValue(self, "triggerHash", &triggerHash);

	ActorAction action = static_cast<ActorAction>(j["action"]);
	il2cpp_utils::SetFieldValue(self, "action", &action);

	//TODO: Figure out where animations are stored or how to create our own
	//public RootMotionReference motionData;
	//private RootMovementCurve position;
	//private RootRotationCurve rotation;
}

void EnemyAction::LoadStopFiring(json j)
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemyActionStopFiring"));
	il2cpp_utils::RunMethod(self, ".ctor");
}
