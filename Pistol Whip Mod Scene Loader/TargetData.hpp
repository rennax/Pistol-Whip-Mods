#ifndef TARGETDATA_HPP
#define TARGETDATA_HPP
#include "List.hpp"
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;



class TargetData
{
	enum class Distance : int {
		Near = 0,
		Middle = 1,
		Far = 2
	};
public:
	TargetData();
	TargetData(Il2CppObject* obj);
	~TargetData();
	Il2CppObject* Load(json j);
private:
	Il2CppObject* self;
};

#endif // !TARGETDATA_HPP


