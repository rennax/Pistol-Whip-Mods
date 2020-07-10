#include "GeoSet.hpp"
#include "AssetBundle.hpp"
#include "GameObject.hpp"

namespace GeoSet {

	GeoSet::GeoSet()
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "GeoSet");
		self = il2cpp_functions::object_new(klass);

		if (!il2cpp_utils::RunMethod(self, ".ctor"))
			LOG("WARNING: Failed to create geoset\n");
		else
			LOG("Created geoset object\n");
	}


	//Il2CppObject* GeoSet::Load(std::string_view path) {
	//	levelPath = path;
	//	std::string totalPath(path);
	//	totalPath += "/level.json";
	//	std::ifstream i(totalPath);
	//	json level;
	//	i >> level;
	//	json geo = level["geoset"];
	//	
	//	std::string assetPath = levelPath + std::string("/static_objects");
	//	assetDB = AssetBundle::LoadFromFile("Custom Levels/x02/static_objects");

	//	LoadDecoratorCubes(geo["decorCubes"]);
	//	LoadChunks(geo["chunks"]);
	//	LoadStaticProps(geo["staticProps"]);
	//	//loadDynamicProps(geo["dynamicProps"]);

	//	il2cpp_utils::SetFieldValue(self, "chunkSize", &chunkSize);
	//	il2cpp_utils::SetFieldValue(self, "scale", &scale);

	//	return self;
	//}

	Il2CppObject* GeoSet::Load(json j)
	{
		json geo = j;

		//TODO change this so path is sent as an argument, or stored in level.json
		assetDB = AssetBundle::LoadFromFile("Custom Levels/x02/static_objects");

		LoadDecoratorCubes(geo["decorCubes"]);
		LoadChunks(geo["chunks"]);
		LoadStaticProps(geo["staticProps"]);

		if (!il2cpp_utils::SetFieldValue(self, "chunkSize", &chunkSize))
			LOG("WARNING: Failed to set chunkSize in GeoSet::Load()\n");

		if (!il2cpp_utils::SetFieldValue(self, "scale", &scale))
			LOG("WARNING: Failed to set scale in GeoSet::Load()\n");

		return self;
	}






	void GeoSet::LoadStaticProps(json j) {

		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "GameObject");
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

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


			Il2CppObject* prefab = AssetBundle::LoadAsset(assetDB, prop["prefabName"], type);
			if (prefab == nullptr)
			{
				std::string pfName = prop["prefabName"];
				LOG("ERROR: GeoSet::loadStaticProps: Prefab %s doesn't exist\n", pfName.c_str());
			}

			//WorldObject::DumpComponents(prefab);

			
			
			//Il2CppObject* LODSwitcher = nullptr;			
			//il2cpp_utils::RunMethod(LODSwitcher, prefab, "GetComponent", GetComponentType(prefab, "", "LODSwitcher"));

			//Il2CppObject* meshFilter = nullptr;
			//il2cpp_utils::RunMethod(meshFilter, prefab, "GetComponent", GetComponentType(prefab, "UnityEngine", "MeshFilter"));

			//


			////int aLevel = prop["prefab"]["aLevel"];
			//int aLevel = 15;
			//auto aMesh = il2cpp_utils::GetFieldValue(meshFilter, "mesh");
			//il2cpp_utils::RunMethod(LODSwitcher, "SetMesh", aMesh, &aLevel);



			WorldObject staticProp(point, prefab, scale);

			staticProps.push_back(staticProp);
		}

		List<Il2CppObject*> staticPropList(il2cpp_utils::GetFieldValue(self, "staticProps"));
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
			Il2CppObject* prefab = AssetBundle::LoadAsset(levelPath + std::string("/static_objects"), prop["prefabName"]);
			WorldObject dynamicProp(point, prefab, scale);
			dynamicProps.push_back(dynamicProp);
		}

		List<Il2CppObject*> staticPropList(il2cpp_utils::GetFieldValue(self, "dynamicProps"));
		for (auto& prop : dynamicProps)
		{
			staticPropList.Add(prop.GetObj());
		}
	}

	void GeoSet::LoadChunks(json j)
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

		List<ChunkMeshData> chunkDataList(il2cpp_utils::GetFieldValue(self, "chunkData"));
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
		List<ChunkMeshSlice> chunkSlicesList(il2cpp_utils::GetFieldValue(self, "chunkSlices"));
		chunkSlicesList.Add(chunkSlice);
	}

	void GeoSet::LoadDecoratorCubes(json j)
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

		List<OscillatingObjectData> decorCubes(il2cpp_utils::GetFieldValue(self, "decoratorCubes"));
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