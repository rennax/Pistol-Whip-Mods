#include "WavLoader.hpp"

WavLoader::WavLoader(std::string_view filename)
{

	std::ifstream f(std::string(filename), std::ios::binary | std::ios::ate);
	if (!f.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
	}
	std::streamsize size = f.tellg();
	f.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if (f.read(buffer.data(), size))
	{
		std::cout << "Successfully copied the files content" << std::endl;
	}

	SubChunk subchunk;
	size_t offset = 0;

	bool readData = false;
	do
	{
		std::memcpy(&subchunk, buffer.data() + offset, sizeof(SubChunk));
		switch (subchunk.ChunkID)
		{
		case ChunkType::RIFF:
			std::memcpy(&riff, buffer.data() + offset, sizeof(RIFFHeader));
			offset += sizeof(RIFFHeader);
			break;
		case ChunkType::ftm:
			std::memcpy(&ftm, buffer.data() + offset, sizeof(ftmHeader));
			offset += sizeof(ftmHeader);
			break;
		case ChunkType::data:
			std::memcpy(&data, buffer.data() + offset, sizeof(dataHeader));
			offset += sizeof(dataHeader);
			readData = true;
			rawData.resize(data.SubchunkSize / 4);
			std::memcpy(rawData.data(), buffer.data() + offset, data.SubchunkSize);
			break;
		default:
			offset += subchunk.ChunkSize + 4 + 4;
			break;
		}
	} while (readData != true);

}

const std::vector<float>& WavLoader::GetData()
{
	return rawData;
}

int WavLoader::NumberOfSamples()
{
	return rawData.size();
}
