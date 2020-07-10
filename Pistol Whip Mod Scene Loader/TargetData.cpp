#include "TargetData.hpp"

TargetData::TargetData()
{
	auto klass = il2cpp_utils::GetClassFromName("", "TargetData");
	self = il2cpp_functions::object_new(klass);
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
	return self;
}
