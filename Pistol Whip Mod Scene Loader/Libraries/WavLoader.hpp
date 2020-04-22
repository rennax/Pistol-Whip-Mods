#pragma once

#include <fstream>
#include <string_view>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//The canonical WAVE format starts with the RIFF header :
//
//0         4   ChunkID          Contains the letters "RIFF" in ASCII form
//(0x52494646 big - endian form).
//4         4   ChunkSize        36 + SubChunk2Size, or more precisely :
//4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
//This is the size of the rest of the chunk
//following this number.This is the size of the
//entire file in bytes minus 8 bytes for the
//two fields not included in this count :
//    ChunkID and ChunkSize.
//    8         4   Format           Contains the letters "WAVE"
//    (0x57415645 big - endian form).
//
//    The "WAVE" format consists of two subchunks : "fmt " and "data" :
//    The "fmt " subchunk describes the sound data's format:
//
//    12        4   Subchunk1ID      Contains the letters "fmt "
//    (0x666d7420 big - endian form).
//    16        4   Subchunk1Size    16 for PCM.This is the size of the
//    rest of the Subchunk which follows this number.
//    20        2   AudioFormat      PCM = 1 (i.e.Linear quantization)
//    Values other than 1 indicate some
//    form of compression.
//    22        2   NumChannels      Mono = 1, Stereo = 2, etc.
//    24        4   SampleRate       8000, 44100, etc.
//    28        4   ByteRate == SampleRate * NumChannels * BitsPerSample / 8
//    32        2   BlockAlign == NumChannels * BitsPerSample / 8
//    The number of bytes for one sample including
//    all channels.I wonder what happens when
//    this number isn't an integer?
//    34        2   BitsPerSample    8 bits = 8, 16 bits = 16, etc.
//    2   ExtraParamSize   if PCM, then doesn't exist
//    X   ExtraParams      space for extra parameters
//
//    The "data" subchunk contains the size of the data and the actual sound :
//
//36        4   Subchunk2ID      Contains the letters "data"
//(0x64617461 big - endian form).
//40        4   Subchunk2Size == NumSamples * NumChannels * BitsPerSample / 8
//This is the number of bytes in the data.
//You can also think of this as the size
//of the read of the subchunk following this
//number.
//44 * Data             The actual sound data.


enum ChunkType : uint32_t{
	RIFF = 0x46464952,
	ftm = 0x20746d66,
	data = 0x61746164
};

struct SubChunk {
	uint32_t ChunkID;
	uint32_t ChunkSize;
};

struct RIFFHeader {
	uint8_t ChunkID[4];
	uint32_t ChunkSize;
	uint8_t Format[4];
};

struct ftmHeader {
	uint8_t ChunkId[4];
	uint32_t SubchunkSize; // 16 for PCM.This is the size of the rest of the Subchunk which follows this number.
	uint16_t AudioFormat; //PCM = 1 (i.e.Linear quantization). Values other than 1 indicate some form of compression.
	uint16_t NumChannels; //Mono = 1, Stereo = 2, etc.
	uint32_t SampleRate; //8000, 44100, etc.
	uint32_t ByteRate; //ByteRate == SampleRate * NumChannels * BitsPerSample / 8
	uint16_t BlockAlign; //BlockAlign == NumChannels * BitsPerSample / 8
};

struct dataHeader {
	uint8_t ChunkId[4];
	uint32_t SubchunkSize; // SubchunkSize == NumSamples * NumChannels * BitsPerSample / 8
};


class WavLoader {
public:
	WavLoader(std::string_view filename);
	const std::vector<float>& GetData();
	int NumberOfSamples();
	inline int SampleRate() { return ftm.SampleRate; }
	inline int NumberOfChannels() { return ftm.NumChannels; }
private:
	RIFFHeader riff;
	ftmHeader ftm;
	dataHeader data;
	std::vector<float> rawData;
};