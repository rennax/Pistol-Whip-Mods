#include "TargetData.hpp"
#include "EnemySequence.hpp"

TargetData::TargetData()
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "TargetData"));
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to construct TargetData object\n");
}

TargetData::TargetData(Il2CppObject* obj) : self(obj)
{
}

TargetData::~TargetData()
{

}

Il2CppObject* TargetData::Load(json j)
{
	distance = static_cast<Distance>(j["distance"]);
	cheevoID = static_cast<CheevoID>(j["cheevoID"]);
	ignoreForLevelRank = j["ignoreForLevelRank"];
	noGround = j["noGround"];
	enemyOffset.position = j["enemyOffset"]["position"];
	enemyOffset.rotation = j["enemyOffset"]["rotation"];

	fireTimes = reinterpret_cast<Array<float>*>(il2cpp_functions::array_new(il2cpp_utils::GetClassFromName("System", "Single"), j["fireTimes"].size()));
	for (size_t i = 0; i < j["fireTimes"].size(); i++)
	{
		fireTimes->values[i] = j["fireTimes"].at(i);
	}

	//TODO EnemySequence class
	EnemySequence es;
	enemySequence = es.Load(j["enemySequence"]);
	if (enemySequence == nullptr)
	{
		LOG("ENEMY SEQEUNCE IS NULL");
	}
	
	il2cpp_utils::SetFieldValue(self, "enemySequence", enemySequence);

	il2cpp_utils::SetFieldValue(self, "fireTimes", fireTimes);
	il2cpp_utils::SetFieldValue(self, "enemyOffset", &enemyOffset);
	il2cpp_utils::SetFieldValue(self, "noGround", &noGround);
	il2cpp_utils::SetFieldValue(self, "ignoreForLevelRank", &ignoreForLevelRank);
	il2cpp_utils::SetFieldValue(self, "cheevoID", &cheevoID);
	il2cpp_utils::SetFieldValue(self, "distance", &distance);

	return self;
}

json TargetData::Dump()
{
	il2cpp_utils::GetFieldValue(&distance, self, "distance");
	il2cpp_utils::GetFieldValue(&enemySequence, self, "enemySequence");
	il2cpp_utils::GetFieldValue(&enemyOffset, self, "enemyOffset");
	il2cpp_utils::GetFieldValue(&ignoreForLevelRank, self, "ignoreForLevelRank");
	il2cpp_utils::GetFieldValue(&fireTimes, self, "fireTimes");
	il2cpp_utils::GetFieldValue(&cheevoID, self, "cheevoID");
	il2cpp_utils::GetFieldValue(&noGround, self, "noGround");

	json j;
	j["distance"] = static_cast<int32_t>(distance);
	j["enemyOffset"]["position"] = enemyOffset.position;
	j["enemyOffset"]["rotation"] = enemyOffset.rotation;
	j["ignoreForLevelRank"] = ignoreForLevelRank;
	j["cheevoID"] = static_cast<int32_t>(cheevoID);
	j["noGround"] = noGround;
	
	j["fireTimes"] = nullptr;
	if (fireTimes != nullptr)
	{
		j["fireTimes"] = {};
		for (size_t i = 0; i < fireTimes->Length(); i++)
		{
			j["fireTimes"].push_back(fireTimes->values[i]);
		}
	}

	j["enemySequence"] = "todo";
	return j;
}
