#ifndef AUDIOCLIP_HPP
#define AUDIOCLIP_HPP

#include "utils.h"
#include "logger.h"


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

struct Wav {
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
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
    Wav wav;
    std::vector<uint8_t> data;
};


inline AudioClip::AudioClip(std::string_view file_, AUDIOFILE fileType) :
    file(file_), type(fileType)
{
    auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "AudioClip");
    audioClip = il2cpp_functions::object_new(klass);
    il2cpp_utils::RunMethod(audioClip, ".ctor");
    
    if (type == AUDIOFILE::WAV)
    {
        LoadWav();
        int offsetSamples = 0;
        il2cpp_utils::RunMethod(audioClip, "SetData", floatData, &offsetSamples);
    }

}

AudioClip::~AudioClip()
{
}

// TODO Optimize this shite
inline void AudioClip::LoadWav()
{
    int headerSize = sizeof(Wav), filelength = 0;

    std::string fname = testPath + file;
    std::FILE* f = std::fopen(fname.c_str(), "r");
    if (!f.is_open())
    {
        LOG("Warning: AudioClip: Failed to open sound file: %s", file.c_str());
        return;
    }

    for (size_t i = 0; i < 4; i++)
    {
        f >> wav.RIFF[i];
    }

    f >> wav.ChunkSize;

    for (size_t i = 0; i < 4; i++)
    {
        f >> wav.WAVE[i];
    }

    for (size_t i = 0; i < 4; i++)
    {
        f >> wav.fmt[i];
    }

    f >> wav.Subchunk1Size;  // Size of the fmt chunk
    f >> wav.AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    f >> wav.NumOfChan;      // Number of channels 1=Mono 2=Sterio
    f >> wav.SamplesPerSec;  // Sampling Frequency in Hz
    f >> wav.bytesPerSec;    // bytes per second
    f >> wav.blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    f >> wav.bitsPerSample;  // Number of bits per sample

    for (size_t i = 0; i < 4; i++)
    {
        f >> wav.Subchunk2ID[i];
    }

    f >> wav.Subchunk2Size;  // Sampled data length

    for (size_t i = 0; i < wav.Subchunk2Size; i++)
    {
        uint8_t tmp;
        f >> tmp;
        data.push_back(tmp);
    }

    
    floatData = il2cpp_utils::CreateIl2CppArray("System", "Single", data.size());
    std::vector<float> floats;
    floats.reserve(data.size()/sizeof(floats));

    std::memcpy(floats.data(), data.data(), data.size());

    for (size_t i = 0; i < floats.size(); i++)
    {
        il2cpp_array_set(floatData, float, i, floats[i]);
    }

    LOG("AudioClip contains %u floats\n", floats.size());
}

#endif // !AUDIOCLIP_HPP
