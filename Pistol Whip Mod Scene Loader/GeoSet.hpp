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


class GeoSet {
public:
	GeoSet()
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GeoSet");
		geoset = il2cpp_functions::object_new(klass);
		
		const MethodInfo* ctor = il2cpp_utils::GetMethod(klass, ".ctor", 0);
		il2cpp_utils::RunMethod(geoset, ctor);
		LOG("Created geoset object\n");
	}
	void loadVerts(std::string_view filename) {
		std::vector<fs::path> paths = getObjectFiles(testPath);
		if (paths.size() == 0)
		{
			LOG("Couldn't find any object files in %s\n", testPath.c_str());
			return;
		}

		std::fstream file(paths[0], std::ios::in | std::ios::app);
		if (!file.is_open())
		{
			LOG("Couldn't open object file %s\n", paths[0].c_str());
			return;
		}
		for (auto& f : paths)
		{
			LOG("Loading %s\n", f.c_str());
		}

		std::vector<int> indices;
		std::vector<Vector3> vertices;
		std::vector<std::string> lines;
		std::vector<int> tris;
		std::string line;
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}


		for (auto& entry : lines)
		{
			std::istringstream ss(entry);
			std::string start;
			ss >> start;
			if (start == "#")
			{

			}
			else if (start == "vt")
			{

			}
			else if (start == "vn")
			{

			}
			else if (start == "v")
			{
				Vector3 v;
				ss >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			else if (start == "f")
			{
				int t1, t2, t3;
				ss >> t1 >> t2 >> t3;
				tris.push_back(t1-1);
				tris.push_back(t2-1);
				tris.push_back(t3-1);
			}
		}
		Vector3i id{0, 0, 0};
		createChunkMeshData(id, vertices, tris);
		//createChunkMeshSlice(-1, vertices, tris);
	}

	Il2CppObject* generateGeoSet() { 
		//Copy ChunkMeshData
		//size_t size = chunkDataVec.size() * sizeof(ChunkMeshData);
		//Il2CppArray* chunkData = il2cpp_utils::CreateIl2CppArray("", "ChunkMeshData", size);
		if (!geoset)
		{
			LOG("ERROR: geoset is not initiated");
			return nullptr;
		}

		il2cpp_utils::SetFieldValue(geoset, "chunkSize", &chunkSize);
		il2cpp_utils::SetFieldValue(geoset, "scale", &scale);

		return geoset; 
	}

	std::string getTestFile()
	{
		return testPath;
	}
public: //Functions to create geoset
	void createChunkMeshData(
			Vector3i id, 
			const std::vector<Vector3>& vertices, 
			const std::vector<int>& triangles) 
	{
		Mesh mesh;
		if (!mesh.Clear() ||
			!mesh.SetVertices(vertices) ||
			!mesh.SetTriangles(triangles))
		{
			LOG("GeoSet::createChunkMeshData failed to create mesh");
			return;
		}

		ChunkMeshData chunkData;
		chunkData.id = id;
		chunkData.verts = mesh.verts;
		chunkData.tris = mesh.tris;
		chunkData.m_liveMesh = mesh.GetMesh();

		List<ChunkMeshData> chunkDataList(il2cpp_utils::GetFieldValue(geoset, "chunkData"));
		chunkDataList.Add(chunkData);

		createChunkMeshSlice(-1, id, mesh);
	}

	void createChunkMeshSlice(
		int z,
		Vector3i id,
		Mesh& mesh)
	{
		ChunkMeshSlice chunkSlice = {
			z,
			mesh.verts,
			nullptr,
			mesh.tris,
			mesh.GetMesh()
		};

		//Add chunkMeshData object to chunkData list object inside geoset
		List<ChunkMeshSlice> chunkSlicesList(il2cpp_utils::GetFieldValue(geoset, "chunkSlices"));
		chunkSlicesList.Add(chunkSlice);
	}

	void loadDecoratorCubes()
	{
		decoratorCubes.clear(); // Make sure that on subsequent calls that the vector is empty
		std::ifstream i(fs::path(testPath + std::string("/") + decorCubeFileName));
		json j;
		i >> j;
		if (j["version"] != 0.1)
		{
			LOG("GeoSet: loadDecoratorCubes() tried to load a file version V%.2f that is not supported", j["version"]);
			return;
		}
		// Parse array containing all objects
		for (auto& elem : j["decorCubes"])
		{
			auto pos = elem["restPoint"];
			decoratorCubes.push_back({
				{pos["x"], pos["y"], pos["z"]},
				elem["moveScale"],
				elem["phase"]
				});
		}

		List<OscillatingObjectData> decorCubes(il2cpp_utils::GetFieldValue(geoset, "decoratorCubes"));
		for (auto& cube : decoratorCubes)
		{
			decorCubes.Add(cube);
		}
	}

private: //Functions
	std::vector<fs::path> getObjectFiles(std::string path) {

		std::vector<fs::path> paths;
		for (const auto& entry : fs::directory_iterator(path))
		{

			if (entry.path().extension() == ".obj")
			{
				LOG("Found an object file, path: %s\n", entry.path().c_str());
				paths.push_back(entry.path());
			}
		}
		return paths;
	}
		
private:
	Il2CppObject* geoset = nullptr;
	std::vector<ChunkMeshData> chunkDataVec;
	std::vector<ChunkMeshSlice> slices;
	std::vector<OscillatingObjectData> decoratorCubes;

	std::string testPath = "Custom Levels/x02";
	std::string decorCubeFileName = "decors.json";
	// Geoset Fields
	Il2CppObject* track = nullptr;			//public TrackData track; // 0x18
	Vector3i chunkSize = {32, 32, 32};		//public Vector3i chunkSize; // 0x20
	float scale = 0.5f;						//public float scale; // 0x2C
	//Il2CppObject* chunkData = nullptr;		//public List<ChunkMeshData> chunkData; // 0x30
	//Il2CppObject* chunkSlices = nullptr;	//public List<ChunkMeshSlice> chunkSlices; // 0x38
	//Il2CppObject* staticProps = nullptr;	//public List<WorldObject> staticProps; // 0x40
	//Il2CppObject* dynamicProps = nullptr;	//public List<WorldObject> dynamicProps; // 0x48
	//Il2CppObject* decoratorCubes = nullptr; //public List<OscillatingObjectData> decoratorCubes; // 0x50

};





};

#endif // !GEOSET_HPP
