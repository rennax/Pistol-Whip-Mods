#include "WorldRegion.hpp"

WorldRegion::WorldRegion(Region type)
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "WorldRegion");
	self = il2cpp_functions::object_new(klass);

	const MethodInfo* ctor = il2cpp_utils::GetMethod(klass, ".ctor", 1);
	il2cpp_utils::RunMethod(self, ctor, &type);
	LOG("Created WorldRegion object\n");
}

WorldRegion::WorldRegion(Il2CppObject* obj) :self(obj)
{
}

WorldRegion::~WorldRegion()
{
}

json WorldRegion::Dump()
{
	json j;
	il2cpp_utils::GetFieldValue(&position, self, "position");
	il2cpp_utils::GetFieldValue(&min, self, "min");
	il2cpp_utils::GetFieldValue(&max, self, "max");
	il2cpp_utils::GetFieldValue(&type, self, "type");

	j["position"] = position;
	j["min"] = min;
	j["max"] = max;
	j["type"] = type;

	return j;
}

Il2CppObject* WorldRegion::Load(json j)
{
	position = j["position"];
	min = j["min"];
	max = j["max"];
	type = j["type"].get<Region>();

	il2cpp_utils::SetFieldValue(self, "position", &position);
	il2cpp_utils::SetFieldValue(self, "min", &min);
	il2cpp_utils::SetFieldValue(self, "max", &max);
	il2cpp_utils::SetFieldValue(self, "type", &type);

	return self;
}
