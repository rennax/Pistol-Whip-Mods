#include "ColorShiftPoint.hpp"

ColorShiftPoint::ColorShiftPoint() {
	auto klass = il2cpp_utils::GetClassFromName("", "ColorShiftPoint");
	object = il2cpp_functions::object_new(klass);
	il2cpp_utils::RunMethod(object, ".ctor");
}

ColorShiftPoint::ColorShiftPoint(Il2CppObject* obj) : object(object) {}

ColorShiftPoint::ColorShiftPoint(int start, int end, ColorData colors)
{
}

Il2CppObject* ColorShiftPoint::Load(json j)
{
	int start = 0;
	int end = 0;
	ColorData colors;

	start = j["start"];
	start = j["end"];

	colors.mainColor.r = j["colors"]["mainColor"]["r"];
	colors.mainColor.g = j["colors"]["mainColor"]["g"];
	colors.mainColor.b = j["colors"]["mainColor"]["b"];
	colors.mainColor.a = j["colors"]["mainColor"]["a"];

	colors.fogColor.r = j["colors"]["fogColor"]["r"];
	colors.fogColor.g = j["colors"]["fogColor"]["g"];
	colors.fogColor.b = j["colors"]["fogColor"]["b"];
	colors.fogColor.a = j["colors"]["fogColor"]["a"];

	colors.glowColor.r = j["colors"]["glowColor"]["r"];
	colors.glowColor.g = j["colors"]["glowColor"]["g"];
	colors.glowColor.b = j["colors"]["glowColor"]["b"];
	colors.glowColor.a = j["colors"]["glowColor"]["a"];

	il2cpp_utils::SetFieldValue(object, "start", &start);
	il2cpp_utils::SetFieldValue(object, "end", &end);
	il2cpp_utils::SetFieldValue(object, "colors", &colors);

	return object;
}

json ColorShiftPoint::Dump()
{
	int start = 0;
	int end = 0;
	ColorData colors;
	il2cpp_utils::GetFieldValue(&start, object, "start");
	il2cpp_utils::GetFieldValue(&end, object, "end");
	il2cpp_utils::GetFieldValue(&colors, object, "colors");

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
