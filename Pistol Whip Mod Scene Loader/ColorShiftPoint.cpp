#include "ColorShiftPoint.hpp"

ColorShiftPoint::ColorShiftPoint() {
	self = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "ColorShiftPoint"));
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to Construct ColorShiftPoint\n");
}

ColorShiftPoint::ColorShiftPoint(Il2CppObject* obj) : self(self) {}

ColorShiftPoint::ColorShiftPoint(int start, int end, ColorData colors)
{
}

Il2CppObject* ColorShiftPoint::Load(json j)
{
	start = j["start"];
	end = j["end"];

	colors.fogColor = j["colors"]["fogColor"];
	colors.mainColor = j["colors"]["mainColor"];
	colors.glowColor = j["colors"]["glowColor"];
	colors.storedEnemyColor = j["colors"]["storedEnemyColor"];
	colors.customEnemyColor = j["colors"]["customEnemyColor"];
	

	il2cpp_utils::SetFieldValue(self, "start", &start);
	il2cpp_utils::SetFieldValue(self, "end", &end);
	il2cpp_utils::SetFieldValue(self, "colors", &colors);

	return self;
}

json ColorShiftPoint::Dump()
{
	il2cpp_utils::GetFieldValue(&start, self, "start");
	il2cpp_utils::GetFieldValue(&end, self, "end");
	il2cpp_utils::GetFieldValue(&colors, self, "colors");

	json j;
	j["start"] = start;
	j["end"] = end;

	j["colors"]["mainColor"]["r"] = colors.mainColor.r;
	j["colors"]["mainColor"]["g"] = colors.mainColor.g;
	j["colors"]["mainColor"]["b"] = colors.mainColor.b;
	j["colors"]["mainColor"]["a"] = colors.mainColor.a;

	j["colors"]["fogColor"]["r"] = colors.fogColor.r;
	j["colors"]["fogColor"]["g"] = colors.fogColor.g;
	j["colors"]["fogColor"]["b"] = colors.fogColor.b;
	j["colors"]["fogColor"]["a"] = colors.fogColor.a;

	j["colors"]["glowColor"]["r"] = colors.glowColor.r;
	j["colors"]["glowColor"]["g"] = colors.glowColor.g;
	j["colors"]["glowColor"]["b"] = colors.glowColor.b;
	j["colors"]["glowColor"]["a"] = colors.glowColor.a;
	
	return j;
}
