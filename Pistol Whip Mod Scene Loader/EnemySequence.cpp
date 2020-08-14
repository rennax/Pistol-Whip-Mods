#include "EnemySequence.hpp"
#include "List.hpp"
#include "EnemyAction.hpp"

using namespace CSharp;

EnemySequence::EnemySequence()
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemySequence"));
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to construct EnemySequence\n");
}

EnemySequence::EnemySequence(Il2CppObject* obj)
{
}

EnemySequence::~EnemySequence()
{
}

Il2CppObject* EnemySequence::Load(json j)
{
	enemyType.toughness = j["enemyType"]["toughness"];
	il2cpp_utils::SetFieldValue(self, "enemyType", &enemyType);

	forceCheevoID = static_cast<CheevoID>(j["forceCheevoID"]);
	il2cpp_utils::SetFieldValue(self, "forceCheevoID", &forceCheevoID);

	playerActionLerp = j["playerActionLerp"];
	il2cpp_utils::SetFieldValue(self, "playerActionLerp", &playerActionLerp);

	localActionPoint.position = j["localActionPoint"]["position"];
	localActionPoint.rotation = j["localActionPoint"]["rotation"];
	il2cpp_utils::SetFieldValue(self, "localActionPoint", &localActionPoint);

	autospawn = j["autospawn"];
	il2cpp_utils::SetFieldValue(self, "autospawn", &autospawn);

	//We might not need to set the action index
	actionIndex = j["actionIndex"];
	il2cpp_utils::SetFieldValue(self, "actionIndex", &actionIndex);

	isThreat = j["isThreat"];
	il2cpp_utils::SetFieldValue(self, "isThreat", &isThreat);

	duration = j["duration"];
	il2cpp_utils::SetFieldValue(self, "duration", &duration);

	List<Il2CppObject*> actions(il2cpp_utils::GetFieldValue(self, "actions"));
	for (size_t i = 0; i < j["actions"].size(); i++)
	{
		EnemyAction action(self);
		actions.Add(action.Load(j["actions"].at(i)));
	}

	//TODO

	//The objects below might be instantiated by the game
	//actionHolder
	//OnSequenceStart
	//OnSequenceStop
	//enemy

	return self;
}

json EnemySequence::Dump()
{

	json j;
	return j;
}
