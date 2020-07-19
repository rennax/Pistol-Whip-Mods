#ifndef TEMPOSECTIONDEF_HPP
#define TEMPOSECTIONDEF_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

class TempoSectionDef
{
public:
	TempoSectionDef();
	~TempoSectionDef();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self = nullptr;
	std::string sectionName;
	int64_t startSample;
	int64_t samplesPerBeat;
	int64_t beatsPerMeasure;
	bool bStartNewMeasure;
};


#endif // !TEMPOSECTIONDEF_HPP
