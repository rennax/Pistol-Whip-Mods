#ifndef WWISEKOREOGRAPHYSET_HPP
#define WWISEKOREOGRAPHYSET_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

class WwiseKoreographySet
{
public:
	WwiseKoreographySet(Il2CppObject* koreo);
	WwiseKoreographySet(Il2CppObject* koreo, Il2CppObject* obj);
	~WwiseKoreographySet();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self = nullptr;
	Il2CppObject* koreo = nullptr;
};


#endif // WWISEKOREOGRAPHYSET_HPP