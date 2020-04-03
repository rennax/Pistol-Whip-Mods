#ifndef GEOSET_HPP
#define GEOSET_HPP
extern "C" {
#include "funchook.h"
}


#include "Mesh.hpp"
#include "il2cpp_utils.hpp"
#include "List.hpp"
#include "logger.h"
#include <filesystem>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <fstream>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace GeoSet {
	using namespace CSharp;
	namespace fs = std::filesystem;

class GeoSet {
public:
	GeoSet()
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GeoSet");
		geoset = il2cpp_functions::object_new(klass);
		
		const MethodInfo* m = il2cpp_utils::GetMethod(klass, ".ctor", 0);
		il2cpp_utils::RunMethod((void*)geoset, m);
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
				/*auto it = std::find(vertices.begin(), vertices.end(), v);
				Vertex already exit, just push the index into indices
				if ( it!= vertices.end())
				{
					indices.push_back(std::distance(vertices.begin(), it));
				}
				else
				{
					vertices.push_back(v);
					indices.push_back(vertices.size() - 1);
				}*/
				vertices.push_back(v);
			}
			else if (start == "f")
			{
				int t1, t2, t3;
				ss >> t1 >> t2 >> t3;
				tris.push_back(t1);
				tris.push_back(t2);
				tris.push_back(t3);
			}
		}
		createChunkMeshData({ -3, -1, -1 }, vertices, tris);
		createChunkMeshSlice(-1, vertices, tris);
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
		List<ChunkMeshData> chunkData(il2cpp_utils::GetFieldValue(geoset, "chunkData"));
		for (size_t i = 0; i < chunkDataVec.size(); i++)
		{
			chunkData.Add(chunkDataVec[i]);
			//il2cpp_array_set(chunkData, ChunkMeshData, i, chunkDataVec[i]);
		}

		List<ChunkMeshSlice> sliceData(il2cpp_utils::GetFieldValue(geoset, "chunkSlices"));
		for (size_t i = 0; i < slices.size(); i++)
		{
			sliceData.Add(slices[i]);
			//il2cpp_array_set(chunkData, ChunkMeshData, i, chunkDataVec[i]);
		}

		//Since we are pulling the instance and creating list based on that, 
		//we shouldn't need to set the field again
 	//	if (il2cpp_utils::SetFieldValue(geoset, "chunkData", chunkData.getInstance()))
		//{
		//	LOG("Failed to set chunkData in geoset\n");
		//}
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
		ChunkMeshData chunk;
		chunk.id = id;

		//Create verts array and assign it
		size_t size = sizeof(Vector3) * vertices.size();
		Il2CppArray* verts = il2cpp_utils::CreateIl2CppArray("UnityEngine", "Vector3", size);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			il2cpp_array_set(verts, Vector3, i, vertices[i]);
		}
		chunk.verts = verts;

		//Create tris array and assign it
		size = sizeof(int) * vertices.size();
		Il2CppArray* tris = il2cpp_utils::CreateIl2CppArray("System", "Int32", size);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			il2cpp_array_set(tris, int, i, triangles[i]);
		}
		chunk.tris = tris;

		//Move final chunk into 
		chunkDataVec.push_back(chunk);
	}

	void createChunkMeshSlice(
		int z,
		const std::vector<Vector3>& vertices,
		const std::vector<int>& triangles)
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "ChunkMeshSlice");
		Il2CppObject* s = il2cpp_functions::object_new(klass);
		auto ctor = il2cpp_utils::GetMethod(klass, ".ctor", 1);
		il2cpp_utils::RunMethod(s, ctor, &z);

		auto meshKlass = il2cpp_utils::GetClassFromName("UnityEngine", "Mesh");
		Il2CppObject* mesh = il2cpp_utils::New(meshKlass);


		ChunkMeshSlice* slice = (ChunkMeshSlice*)il2cpp_functions::object_unbox(s);
		slice->m_liveMesh = mesh;
		//Create verts array and assign it
		size_t size = sizeof(Vector3) * vertices.size();
		Il2CppArray* verts = il2cpp_utils::CreateIl2CppArray("UnityEngine", "Vector3", size);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			il2cpp_array_set(verts, Vector3, i, vertices[i]);
		}
		slice->verts = verts;

		//Create tris array and assign it
		size = sizeof(int) * triangles.size();
		Il2CppArray* tris = il2cpp_utils::CreateIl2CppArray("System", "Int32", size);
		for (size_t i = 0; i < triangles.size(); i++)
		{
			il2cpp_array_set(tris, int, i, triangles[i]);
		}
		slice->tris = tris;


		auto generateMesh = il2cpp_utils::GetMethod(klass, "get_mesh", 0);
		il2cpp_utils::RunMethod(il2cpp_functions::value_box(klass, slice), generateMesh);

		//Move final chunk into 
		slices.push_back(*slice);

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

	std::string testPath = "Custom Levels/x01";
	// Geoset Fields
	Il2CppObject* track = nullptr;			//public TrackData track; // 0x18
	Vector3i chunkSize = {1, 1, 1};			//public Vector3i chunkSize; // 0x20
	float scale = 1;						//public float scale; // 0x2C
	Il2CppObject* chunkData = nullptr;		//public List<ChunkMeshData> chunkData; // 0x30
	Il2CppObject* chunkSlices = nullptr;	//public List<ChunkMeshSlice> chunkSlices; // 0x38
	Il2CppObject* staticProps = nullptr;	//public List<WorldObject> staticProps; // 0x40
	Il2CppObject* dynamicProps = nullptr;	//public List<WorldObject> dynamicProps; // 0x48
	Il2CppObject* decoratorCubes = nullptr; //public List<OscillatingObjectData> decoratorCubes; // 0x50

};





};

#endif // !GEOSET_HPP
