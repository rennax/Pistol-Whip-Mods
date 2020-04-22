#include "GeoSet.hpp"
#include "AssetBundle.hpp"

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


	Il2CppObject* GeoSet::Load(std::string_view path) {
		levelPath = path;
		std::string totalPath(path);
		totalPath += "/level.json";
		std::ifstream i(totalPath);
		json level;
		i >> level;
		json geo = level["geoset"];
		


		loadDecoratorCubes(geo["decorCubes"]);
		loadChunks(geo["chunks"]);
		loadStaticProps(geo["staticProps"]);
		loadDynamicProps(geo["dynamicProps"]);

		il2cpp_utils::SetFieldValue(geoset, "chunkSize", &chunkSize);
		il2cpp_utils::SetFieldValue(geoset, "scale", &scale);

		return geoset;
	}


// PRIVATE FUNCTIONS

	void GeoSet::loadStaticProps(json j) {
		for (auto& prop : j)
		{
			json p = prop["point"]["position"];
			json r = prop["point"]["rotation"];
			json s = prop["scale"];
			
			WorldPoint point = {
				{p["x"], p["y"], p["z"]},
				{r["x"], r["y"], r["z"], r["w"]}
			};
			Vector3 scale = {
				s["x"],
				s["y"],
				s["z"]
			};
			Il2CppObject* prefab = AssetBundle::LoadAsset(levelPath + std::string("/assets"), prop["prefabName"]);
			WorldObject staticProp(point, prefab, scale);
			staticProps.push_back(staticProp);
		}

		List<Il2CppObject*> staticPropList(il2cpp_utils::GetFieldValue(geoset, "staticProps"));
		for (auto& prop : staticProps)
		{
			staticPropList.Add(prop.GetObj());
		}
	}

	void GeoSet::loadDynamicProps(json j) {
		for (auto& prop : j)
		{
			json p = prop["point"]["position"];
			json r = prop["point"]["rotation"];
			json s = prop["scale"];

			WorldPoint point = {
				{p["x"], p["y"], p["z"]},
				{r["x"], r["y"], r["z"], r["w"]}
			};
			Vector3 scale = {
				s["x"],
				s["y"],
				s["z"]
			};
			Il2CppObject* prefab = AssetBundle::LoadAsset(levelPath + std::string("/assets"), prop["prefabName"]);
			WorldObject dynamicProp(point, prefab, scale);
			dynamicProps.push_back(dynamicProp);
		}

		List<Il2CppObject*> staticPropList(il2cpp_utils::GetFieldValue(geoset, "dynamicProps"));
		for (auto& prop : dynamicProps)
		{
			staticPropList.Add(prop.GetObj());
		}
	}

	void GeoSet::loadChunks(json j)
	{
		// Parse array containing all objects
		for (auto& elem : j)
		{
			Vector3i id = { 
				elem["id"]["x"],
				elem["id"]["y"],
				elem["id"]["z"]
			};

			std::string objPath = levelPath + std::string("/") + std::string(elem["name"]);
			ObjFile obj = loadObjectFile(objPath);
			createChunkMeshData(id, obj.vertices, obj.tris);
		}
	}

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
		// Parse array containing all objects
		for (auto& elem : j)
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

	ObjFile GeoSet::loadObjectFile(std::string_view filename) {
		ObjFile obj;

		std::fstream file(filename, std::ios::in | std::ios::app);
		if (!file.is_open())
		{
			LOG("Couldn't open object file %s\n", filename.data());
			return obj;
		}

		std::vector<std::string> lines;

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
				obj.vertices.push_back(v);
			}
			else if (start == "f")
			{
				int t1, t2, t3;
				ss >> t1 >> t2 >> t3;
				obj.tris.push_back(t1 - 1);
				obj.tris.push_back(t2 - 1);
				obj.tris.push_back(t3 - 1);
			}
		}
		return obj;
	}
};