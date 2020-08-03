#ifndef KOREOGRAPHYEVENT_HPP
#define KOREOGRAPHYEVENT_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


class KoreographyEvent
{
public:
	KoreographyEvent();
	KoreographyEvent(Il2CppObject* obj);
	~KoreographyEvent();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self = nullptr;
	int64_t mStartSample;
	int64_t mEndSample;
	Il2CppObject* mPayload = nullptr;
};

#endif // !KOREOGRAPHYEVENT_HPP
