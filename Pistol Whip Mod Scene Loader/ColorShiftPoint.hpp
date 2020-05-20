#ifndef COLORSHIFTPOINT_HPP
#define COLORSHIFTPOINT_HPP

#include "il2cpp_utils.hpp"
#include <string_view>
#include "json.hpp"

using json = nlohmann::json;

typedef struct ColorData {
	Color mainColor;
	Color fogColor;
	Color glowColor;
} ColorData;

class ColorShiftPoint {
public:
	ColorShiftPoint();
	ColorShiftPoint(Il2CppObject* obj);
	ColorShiftPoint(int start, int end, ColorData colors);
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* object;
};


#endif // !COLORSHIFTPOINT_HPP


