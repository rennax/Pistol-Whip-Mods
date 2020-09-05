#include "WorldVolume.hpp"

WorldVolume::WorldVolume()
{
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "WorldVolume"));
}

WorldVolume::~WorldVolume()
{
}

Il2CppObject* WorldVolume::Load(json j)
{
	position = j["position"];
	//TODO determine if we use size or min/max	
	//min = j["min"];
	//max = j["max"];
	size = j["size"];
	type = static_cast<GeoVolume>(j["type"]);

	il2cpp_utils::RunMethod(self, ".ctor", &type, &position, &size);
	return self;
}
