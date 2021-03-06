#include "EnemySequence.hpp"
#include "List.hpp"
#include "EnemyAction.hpp"
#include "GameObject.hpp"

using namespace CSharp;

EnemySequence::EnemySequence()
{
	gameObject = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
	self = GameObject::AddComponent(gameObject, il2cpp_utils::GetClassFromName("", "EnemySequence"));
	//self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "EnemySequence"));
	//if (!il2cpp_utils::RunMethod(self, ".ctor"))
	//	LOG("WARNING: Failed to construct EnemySequence\n");
	//Il2CppObject* transform = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"));
	//if (!il2cpp_utils::RunMethod(transform, ".ctor"))
	//	LOG("WARNING: Failed to construct EnemySequence\n");
	//il2cpp_utils::SetFieldValue(self, "transform", transform);

	//il2cpp_utils::RunMethod(self, "Start");
}

EnemySequence::EnemySequence(Il2CppObject* obj) : self(obj)
{
}

EnemySequence::~EnemySequence()
{
}

Il2CppObject* EnemySequence::Load(json j)
{
	//enemyType.toughness = j["enemyType"]["toughness"];
	//il2cpp_utils::SetFieldValue(self, "enemyType", &enemyType);

	forceCheevoID = static_cast<CheevoID>(j["forceCheevoID"]);
	il2cpp_utils::SetFieldValue(self, "forceCheevoID", &forceCheevoID);

	playerActionLerp = j["playerActionLerp"];
	il2cpp_utils::SetFieldValue(self, "playerActionLerp", &playerActionLerp);

	//localActionPoint.position = j["localActionPoint"]["position"];
	//localActionPoint.rotation = j["localActionPoint"]["rotation"];
	//il2cpp_utils::SetFieldValue(self, "localActionPoint", &localActionPoint);

	autospawn = j["autospawn"];
	il2cpp_utils::SetFieldValue(self, "autospawn", &autospawn);

	//We might not need to set the action index
	//actionIndex = j["actionIndex"];
	//il2cpp_utils::SetFieldValue(self, "actionIndex", &actionIndex);

	isThreat = j["isThreat"];
	il2cpp_utils::SetFieldValue(self, "isThreat", &isThreat);

	duration = j["duration"];
	il2cpp_utils::SetFieldValue(self, "duration", &duration);

	actionHolder = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
	il2cpp_utils::SetFieldValue(self, "actionHolder", actionHolder);
	GameObject::SetName(actionHolder, "ActionHolder");
	GameObject::SetParent(gameObject, actionHolder);

	List<Il2CppObject*> actions(il2cpp_utils::GetFieldValue(self, "actions"));
	for (size_t i = 0; i < j["actions"].size(); i++)
	{
		if (j["actions"].at(i).is_null()) continue;
		EnemyAction action(self);
		actions.Add(action.Load(j["actions"].at(i), actionHolder));
	}

	////Do we need to set something?
	//actor = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "Enemy"));
	//il2cpp_utils::RunMethod(actor, ".ctor");
	//il2cpp_utils::SetFieldValue(self, "actor", actor);

	//TODO

	//The objects below might be instantiated by the game
	//actionHolder
	//OnSequenceStart
	//OnSequenceStop

	static auto set_enabled = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("", "EnemySequence"), "enabled");
	bool enabled = false;
	il2cpp_utils::RunMethod(self, set_enabled, &enabled);

	return self;
}

json EnemySequence::Dump()
{

	json j;
	return j;
}
