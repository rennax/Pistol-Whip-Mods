#ifndef WWISEKOREOMEDIAIDENTRY_HPP
#define WWISEKOREOMEDIAIDENTRY_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


class WwiseKoreoMediaIDEntry
{
public:
	WwiseKoreoMediaIDEntry();
	~WwiseKoreoMediaIDEntry();
	Il2CppObject* Load(json j, Il2CppObject* koreo);
private:
	Il2CppObject* self = nullptr;
	uint32_t mediaID = 0;
};


#endif // !WWISEKOREOMEDIAIDENTRY_HPP
