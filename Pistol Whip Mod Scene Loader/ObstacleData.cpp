#include "ObstacleData.hpp"

ObstacleData::ObstacleData()
{
    auto klass = il2cpp_utils::GetClassFromName("", "ObstacleData");
    self = il2cpp_functions::object_new(klass);
    if (!il2cpp_utils::RunMethod(self, ".ctor"))
        LOG("WARNING: Failed to construct ObstacleData object\n");
}

ObstacleData::ObstacleData(Il2CppObject* obj)
{
}

ObstacleData::~ObstacleData()
{
}

Il2CppObject* ObstacleData::Load(json j)
{
    placement = j["placement"];
    if (!il2cpp_utils::SetFieldValue(self, "placement", &placement))
        LOG("WARNING: Failed to assign placement in ObstacleData\n");
    
    type = j["type"];
    if (!il2cpp_utils::SetFieldValue(self, "type", &type))
        LOG("WARNING: Failed to assign type in ObstacleData\n");

    return self;
}
