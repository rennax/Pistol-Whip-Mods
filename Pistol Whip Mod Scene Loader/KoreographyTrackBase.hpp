#ifndef KOREOGRAPHYTRACKBASE_HPP
#define KOREOGRAPHYTRACKBASE_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

class KoreographyTrackBase
{
public:
	KoreographyTrackBase();
	KoreographyTrackBase(Il2CppObject* obj);
	~KoreographyTrackBase();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self;
	std::string mEventID;

};

#endif // !KOREOGRAPHYTRACKBASE_HPP
