#include "GeoSet.hpp"

namespace GeoSet {
// PUBLIC FUNCTIONS
	GeoSet::GeoSet()
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GeoSet");
		geoset = il2cpp_functions::object_new(klass);

		const MethodInfo* ctor = il2cpp_utils::GetMethod(klass, ".ctor", 0);
		il2cpp_utils::RunMethod(geoset, ctor);
		LOG("Created geoset object\n");
	}

	Il2CppObject* GeoSet::generateGeoSet() {
		if (!geoset)
		{
			LOG("ERROR: geoset is not initiated");
			return nullptr;
		}

		il2cpp_utils::SetFieldValue(geoset, "chunkSize", &chunkSize);
		il2cpp_utils::SetFieldValue(geoset, "scale", &scale);

		return geoset;
	}


// PRIVATE FUNCTIONS

	void GeoSet::createChunkMeshData(
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

	void GeoSet::createChunkMeshSlice(
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

	void GeoSet::loadDecoratorCubes(json j)
	{
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

	std::vector<fs::path> GeoSet::getObjectFiles(std::string path) {

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

	void GeoSet::loadVerts(std::string_view filename) {
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
				tris.push_back(t1 - 1);
				tris.push_back(t2 - 1);
				tris.push_back(t3 - 1);
			}
		}
		Vector3i id{ 0, 0, 0 };
		createChunkMeshData(id, vertices, tris);
	}
};