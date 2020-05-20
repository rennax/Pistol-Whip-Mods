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
	Vector3i position, min, max;
	Region type;
	il2cpp_utils::GetFieldValue(&position, self, "position");
	il2cpp_utils::GetFieldValue(&min, self, "min");
	il2cpp_utils::GetFieldValue(&max, self, "max");
	il2cpp_utils::GetFieldValue(&type, self, "type");


	return json();
}

Il2CppObject* WorldRegion::Load(json j)
{
	return nullptr;
}
