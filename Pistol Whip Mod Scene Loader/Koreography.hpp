#ifndef KOREOGRAPHY_HPP
#define KOREOGRAPHY_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"


using json = nlohmann::json;

class Koreography
{
public:
	Koreography();
	Koreography(Il2CppObject* obj);
	~Koreography();
	Il2CppObject* Load(json j);
	json Dump();
private:
	Il2CppObject* self;
	std::string mAudioFilePath;
	int32_t mSampleRate;
	bool mIgnoreLatencyOffset;
	std::string clipName;
	int32_t lastUpdateStart;
	int32_t lastUpdateEnd;

};


#endif // !KOREOGRAPHY_HPP
