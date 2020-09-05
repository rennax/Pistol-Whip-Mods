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

	Il2CppObject* GeoSet::Load(json j)
	{
		//TODO change this so path is sent as an argument, or stored in level.json
		assetBundlePath = "Custom Levels/" + j["mapID"].get<std::string>() + "/";

		LoadDecoratorCubes(j["decorCubes"]);
		LoadChunks(j["chunks"]);
		LoadStaticProps(j["staticProps"]);

		if (!il2cpp_utils::SetFieldValue(self, "chunkSize", &chunkSize))
			LOG("WARNING: Failed to set chunkSize in GeoSet::Load()\n");

		if (!il2cpp_utils::SetFieldValue(self, "scale", &scale))
			LOG("WARNING: Failed to set scale in GeoSet::Load()\n");

		return self;
	}


	void GeoSet::LoadStaticProps(json j) {

		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "GameObject");
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

		std::string staticPropsDBPath = assetBundlePath + "static props";
		Il2CppObject* staticPropsDB = AssetBundle::LoadFromFile(staticPropsDBPath);
		List<Il2CppObject*> staticPropList(il2cpp_utils::GetFieldValue(self, "staticProps"));
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


			Il2CppObject* prefab = AssetBundle::LoadAsset(staticPropsDB, prop["prefabName"], type);
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
			staticPropList.Add(staticProp.GetObj());
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
		static auto getMeshProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "MeshFilter"), "mesh");
		static auto meshVerticesProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "vertices");
		static auto meshTrianglesProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "triangles");
		static auto meshColorsGetProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "colors");

		
		std::string chunkDBPath = assetBundlePath + "chunks";
		Il2CppObject* chunkDB = AssetBundle::LoadFromFile(chunkDBPath);
		if (chunkDB == nullptr)
		{
			LOG("Failed to open %s, are you sure it exists?\n", chunkDBPath.c_str());
		}


		List<ChunkMeshSlice> chunkSlices(il2cpp_utils::GetFieldValue(self, "chunkSlices"));
		List<ChunkMeshData> chunkData(il2cpp_utils::GetFieldValue(self, "chunkData"));

		//We use the mesh to create both the chunksMeshSlice and the chunkMeshData for given chunk
		for (auto c : j)
		{
			Il2CppObject* chunk = AssetBundle::LoadAsset(chunkDB, c["chunkID"]);
			
			Il2CppObject* mesh = nullptr;
			Il2CppObject* meshGO = nullptr;

			//Array<Il2CppObject*>* filters = GameObject::GetComponentsInChildren(chunk, false, "UnityEngine", "MeshFilter");
			//if (filters != nullptr && filters->Length() > 0)
			//{
			//	meshFilter = filters->values[0];
			//}
			//else continue;

			Il2CppObject* meshFilter = GameObject::GetComponentInChildren(chunk, false, "UnityEngine", "MeshFilter");

			il2cpp_utils::RunMethod(&mesh, meshFilter, getMeshProperty);

			ChunkMeshSlice slice;
			slice.z = c["id"]["z"];
			slice.meshSizes = nullptr;
			slice.m_liveMesh = mesh;
			il2cpp_utils::RunMethod(&slice.tris, mesh, meshTrianglesProperty);
			il2cpp_utils::RunMethod(&slice.verts, mesh, meshVerticesProperty);
			il2cpp_utils::RunMethod(&slice.colors, mesh, meshColorsGetProperty);
			//auto sliceBoxed = il2cpp_functions::value_box(il2cpp_utils::GetClassFromName("", "ChunkMeshSlice"), &slice);
			//il2cpp_utils::SetFieldValue(sliceBoxed, "m_liveMesh", mesh);
			//il2cpp_utils::SetFieldValue(sliceBoxed, "verts", il2cpp_utils::GetFieldValue(mesh, "vertices"));
			//il2cpp_utils::SetFieldValue(sliceBoxed, "tris", il2cpp_utils::GetFieldValue(mesh, "triangles"));
			chunkSlices.Add(slice);

			ChunkMeshData data;
			data.id = c["id"];
			data.meshSizes = nullptr;
			data.m_liveMesh = mesh;
			il2cpp_utils::RunMethod(&data.tris, mesh, meshTrianglesProperty);
			il2cpp_utils::RunMethod(&data.verts, mesh, meshVerticesProperty);
			il2cpp_utils::RunMethod(&data.colors, mesh, meshColorsGetProperty);
			//auto dataBoxed = il2cpp_functions::value_box(il2cpp_utils::GetClassFromName("", "ChunkMeshData"), &data);
			//il2cpp_utils::SetFieldValue(dataBoxed, "m_liveMesh", mesh);
			//il2cpp_utils::SetFieldValue(dataBoxed, "verts", il2cpp_utils::GetFieldValue(mesh, "vertices"));
			//il2cpp_utils::SetFieldValue(dataBoxed, "tris", il2cpp_utils::GetFieldValue(mesh, "triangles"));
			chunkData.Add(data);
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

	void GeoSet::LoadChunkMeshSlices(json j)
	{

	}

	void GeoSet::LoadChunkMeshData(json j)
	{
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