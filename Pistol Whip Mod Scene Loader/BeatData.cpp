#include "BeatData.hpp"
#include "WorldObject.hpp"

BeatData::BeatData(float time)
{
	auto klass = il2cpp_utils::GetClassFromName("", "BeatData");
	beatData = il2cpp_functions::object_new(klass);
	il2cpp_utils::RunMethod(beatData, ".ctor", &time);
}

BeatData::BeatData(Il2CppObject* obj) : beatData(obj)
{
}

CSharp::List<Il2CppObject*> BeatData::GetTargets()
{
	return CSharp::List<Il2CppObject*>(il2cpp_utils::GetFieldValue(beatData, "targets"));
}

CSharp::List<Il2CppObject*> BeatData::GetObstacles()
{
	return CSharp::List<Il2CppObject*>(il2cpp_utils::GetFieldValue(beatData, "obstacles"));
}

float BeatData::GetTime()
{
	float time = 0;
	il2cpp_utils::GetFieldValue(&time, beatData, "time");
	return time;
}

void BeatData::Load(std::string_view path)
{
}

json BeatData::DumpToJson()
{
	json j;

	auto obstacles = GetObstacles();
	for (size_t i = 0; i < obstacles.Count(); i++)
	{
		Il2CppObject* obstacle = obstacles[i];
		int placement = -1337;
		int type = -1;
		il2cpp_utils::GetFieldValue(&placement, obstacle, "placement");
		il2cpp_utils::GetFieldValue(&type, obstacle, "type");
		
		Vector3 localPosition;
		auto method = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("", "ObstacleData"), "localPosition");
		il2cpp_utils::RunMethod(&localPosition, obstacle, method);
		
		
		json tmp;
		tmp["placement"] = placement;
		tmp["obstacle_type"] = type;
		tmp["local_position"]["x"] = localPosition.x;
		tmp["local_position"]["y"] = localPosition.y;
		tmp["local_position"]["z"] = localPosition.z;
		j["obstacles"].push_back(tmp);
	}

	auto targets = GetTargets();
	for (size_t i = 0; i < targets.Count(); i++)
	{
		Il2CppObject* target = targets[i];
		int distance;
		Vector2 placement;
		int toughness;
		// EnemySequence
		WorldPoint enemyOffset;
		bool ignoreForLevelRank;
		Il2CppArray* fireTimes;
		int cheevoID;
		bool noGround;

		il2cpp_utils::GetFieldValue(&distance, target, "distance");
		il2cpp_utils::GetFieldValue(&placement, target, "placement");
		il2cpp_utils::GetFieldValue(&toughness, target, "toughness");
		il2cpp_utils::GetFieldValue(&enemyOffset, target, "enemyOffset");
		il2cpp_utils::GetFieldValue(&ignoreForLevelRank, target, "ignoreForLevelRank");
		il2cpp_utils::GetFieldValue(&fireTimes, target, "fireTimes");
		il2cpp_utils::GetFieldValue(&cheevoID, target, "cheevoID");

		json tmp;
		tmp["distance"] = distance;

		tmp["placement"]["x"] = placement.x;
		tmp["placement"]["y"] = placement.y;

		tmp["toughness"] = toughness;

		tmp["enemyOffset"]["position"]["x"] = enemyOffset.position.x;
		tmp["enemyOffset"]["position"]["y"] = enemyOffset.position.y;
		tmp["enemyOffset"]["position"]["z"] = enemyOffset.position.z;

		tmp["enemyOffset"]["rotation"]["x"] = enemyOffset.rotation.x;
		tmp["enemyOffset"]["rotation"]["y"] = enemyOffset.rotation.y;
		tmp["enemyOffset"]["rotation"]["z"] = enemyOffset.rotation.z;
		tmp["enemyOffset"]["rotation"]["w"] = enemyOffset.rotation.w;

		tmp["ignoreForLevelRank"] = ignoreForLevelRank;

		for (size_t i = 0; i < il2cpp_functions::array_length(fireTimes); i++)
		{
			float fireTime = il2cpp_array_get(fireTimes, float, i);
			tmp["fireTimes"].push_back(fireTime);
		}

		tmp["cheevoID"] = cheevoID;

		tmp["noGround"] = noGround;

		j["targets"].push_back(tmp);
	}


	j["time"] = GetTime();
	return j;
}
