#ifndef COLORSHIFTPOINT_HPP
#define COLORSHIFTPOINT_HPP

#include "il2cpp_utils.hpp"
#include <string_view>
#include "json.hpp"

typedef struct ColorData {
	Color mainColor;
	Color fogColor;
	Color glowColor;
} ColorData;


class ColorShiftPoint {
public:
	ColorShiftPoint() {
		auto klass = il2cpp_utils::GetClassFromName("", "ColorShiftPoint");
		object = il2cpp_functions::object_new(klass);
		il2cpp_utils::RunMethod(object, ".ctor");
	}
	ColorShiftPoint(Il2CppObject* obj) : object(object) {}
	void Load(std::string_view) {};
	void Load(nlohmann::json json) {}
private:
	Il2CppObject* object;
};


#endif // !COLORSHIFTPOINT_HPP


