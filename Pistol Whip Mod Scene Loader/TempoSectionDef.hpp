#ifndef TEMPOSECTIONDEF_HPP
#define TEMPOSECTIONDEF_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

class TempoSectionDef
{
public:
	TempoSectionDef();
	TempoSectionDef(Il2CppObject* obj);
	~TempoSectionDef();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self = nullptr;
	std::string sectionName = "";
	int64_t startSample = 0;
	double samplesPerBeat = 0;
	int64_t beatsPerMeasure = 0;
	bool bStartNewMeasure = false;
};


#endif // !TEMPOSECTIONDEF_HPP
