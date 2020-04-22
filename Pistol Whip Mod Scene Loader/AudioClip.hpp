#ifndef AUDIOCLIP_HPP
#define AUDIOCLIP_HPP

#include "utils.h"
#include "logger.h"
#include "Libraries/WavLoader.hpp"


#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

enum class AUDIOFILE {
	OGG,
	WAV,
	MP3,
	DEFAULT = 0
};

class AudioClip
{
public:
	AudioClip(std::string_view file_, AUDIOFILE fileType);
	~AudioClip();
    Il2CppObject* GetAudioClip() { return audioClip; }
private:
    void LoadWav();

private:
    std::string file;
    std::string testPath = "Custom Levels/x02/";
    AUDIOFILE type;

    Il2CppArray* floatData = nullptr;
    Il2CppObject* audioClip = nullptr;
    WavLoader wav;
};


inline AudioClip::AudioClip(std::string_view file_, AUDIOFILE fileType) :
    file(file_), type(fileType), wav(testPath + file)
{
    auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
    audioClip = il2cpp_functions::object_new(klass);
    if (!il2cpp_utils::RunMethod(audioClip, ".ctor"))
        LOG("WARNING: AudioClip: Failed to call .ctor()\n");
    
    
    if (type == AUDIOFILE::WAV)
    {
        LoadWav();
        int offsetSamples = 0;
        int sampleLen = wav.NumberOfSamples();
        int sampleRate = wav.SampleRate();
        int channels = wav.NumberOfChannels();
        bool isStream = false;
        il2cpp_utils::RunMethod(&audioClip, klass, "Create", il2cpp_utils::createcsstr(file_), &sampleLen, &channels, &sampleRate, &isStream);
        bool res = false;
        auto method = il2cpp_utils::GetMethod(klass, "SetData", 2);
        il2cpp_utils::RunMethod(audioClip, method, floatData, &offsetSamples);
    }

}

AudioClip::~AudioClip()
{
}

// TODO Optimize this shite
inline void AudioClip::LoadWav()
{
    auto data = wav.GetData();
    floatData = il2cpp_utils::CreateIl2CppArray("System", "Single", data.size() * sizeof(float));

    for (size_t i = 0; i < data.size(); i++)
    {
        il2cpp_array_set(floatData, float, i, data[i]);
    }

    LOG("AudioClip contains %u floats\n", data.size());
    LOG("Allocated array size %u\n", il2cpp_functions::array_length(floatData));
}

#endif // !AUDIOCLIP_HPP
