#ifndef GEOSET_HPP
#define GEOSET_HPP
extern "C" {
#include "funchook.h"
}


#include "Mesh.hpp"
#include "WorldObject.hpp"
#include "utils.h"
#include "List.hpp"
#include "logger.h"


#include <filesystem>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>


namespace GeoSet {
	using namespace CSharp;
	namespace fs = std::filesystem;
	using json = nlohmann::json;

typedef struct OscillatingObjectData {
	Vector3 restPoint;
	float moveScale;
	float phase;
} OscillatingObjectData;

typedef struct ObjFile {
	std::vector<Vector3> vertices;
	std::vector<int> tris;
} ObjFile;


class GeoSet {
public:
	GeoSet();

	Il2CppObject* Load(std::string_view path);
private: //Functions
	void createChunkMeshData(
		Vector3i id,
		const std::vector<Vector3>& vertices,
		const std::vector<int>& triangles);

	void createChunkMeshSlice(
		int z,
		Vector3i id,
		Mesh& mesh);

	ObjFile loadObjectFile(std::string_view filename);
	void loadDecoratorCubes(json j);
	void loadChunks(json j);
	void loadStaticProps(json j);
	void loadDynamicProps(json j);
private:
	Il2CppObject* geoset = nullptr;
	std::vector<ChunkMeshData> chunkDataVec;
	std::vector<ChunkMeshSlice> slices;
	std::vector<OscillatingObjectData> decoratorCubes;
	std::vector<WorldObject> staticProps;
	std::vector<WorldObject> dynamicProps;

	std::string levelPath = "Custom Levels/x02";
	std::string decorCubeFileName = "decors.json";
	Il2CppObject* assetDB;
	std::vector<Il2CppObject*> prefabs;
	// Geoset Fields
	Vector3i chunkSize = {32, 32, 32};		//public Vector3i chunkSize; // 0x20
	float scale = 0.5f;						//public float scale; // 0x2C

};





};

#endif // !GEOSET_HPP
