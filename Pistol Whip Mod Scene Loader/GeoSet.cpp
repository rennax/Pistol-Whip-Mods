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

	Il2CppObject* GeoSet::Load(json j, fs::path path)
	{
		pathToLevelDir = path;

		//TODO change this so path is sent as an argument, or stored in level.json
		assetBundlePath = pathToLevelDir.generic_string();

		LoadDecoratorCubes(j["decorCubes"]);
		LoadChunks(j);
		LoadStaticProps(j["staticProps"]);

		chunkSize = j["chunkSize"];
		if (!il2cpp_utils::SetFieldValue(self, "chunkSize", &chunkSize))
			LOG("WARNING: Failed to set chunkSize in GeoSet::Load()\n");

		scale = j["scale"];
		if (!il2cpp_utils::SetFieldValue(self, "scale", &scale))
			LOG("WARNING: Failed to set scale in GeoSet::Load()\n");

		return self;
	}


	void GeoSet::LoadStaticProps(json j) {

		auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "GameObject");
		auto type = il2cpp_functions::type_get_object(il2cpp_functions::class_get_type_const(klass));

		//std::string staticPropsDBPath =.generic_string();
		Il2CppObject* staticPropsDB = AssetBundle::LoadFromFile(pathToLevelDir.append("static props").generic_string());
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
		
		static auto meshVerticesGetProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "vertices");
		static auto meshTrianglesGetProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "triangles");
		static auto meshColorsGetProperty = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "colors");
		
		static auto meshVerticesSetProperty = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "vertices");
		static auto meshTrianglesSetProperty = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "triangles");
		static auto meshColorsSetProperty = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"), "colors");
		

		List<ChunkMeshSlice> chunkSlices(il2cpp_utils::GetFieldValue(self, "chunkSlices"));
		List<ChunkMeshData> chunkData(il2cpp_utils::GetFieldValue(self, "chunkData"));

		fs::path chunkDBPath = pathToLevelDir.append(j["chunkDBName"].get<std::string>());
		Il2CppObject* chunkDB = AssetBundle::LoadFromFile(chunkDBPath.generic_string());
		if (chunkDB == nullptr)
		{
			LOG("Failed to open %s, are you sure it exists?\n", chunkDBPath.c_str());
		}

		//We use the mesh to create both the chunksMeshSlice and the chunkMeshData for given chunk
		for (auto c : j["chunkData"])
		{
			std::string meshName = std::string("mesh_") + std::to_string(c["id"]["z"].get<int>());
			std::string chunkName = std::string("chunk_") + std::to_string(c["id"]["z"].get<int>());
			Il2CppObject* chunk = AssetBundle::LoadAsset(chunkDB, chunkName);

			Il2CppObject* mesh = AssetBundle::LoadAsset(chunkDB, meshName);
			Il2CppObject* meshGO = nullptr;

			Il2CppObject* meshFilter = GameObject::GetComponent(chunk, "UnityEngine", "MeshFilter");
			il2cpp_utils::RunMethod(&mesh, meshFilter, getMeshProperty);


			ChunkMeshSlice slice;
			slice.z = c["id"]["z"];
			slice.meshSizes = nullptr;
			slice.m_liveMesh = mesh;
			il2cpp_utils::RunMethod(&slice.tris, mesh, meshTrianglesGetProperty);
			il2cpp_utils::RunMethod(&slice.verts, mesh, meshVerticesGetProperty);
			il2cpp_utils::RunMethod(&slice.colors, mesh, meshColorsGetProperty);
			chunkSlices.Add(slice);

			ChunkMeshData data;
			data.id = c["id"];
			data.meshSizes = nullptr;
			data.m_liveMesh = mesh;
			il2cpp_utils::RunMethod(&data.tris, mesh, meshTrianglesGetProperty);
			il2cpp_utils::RunMethod(&data.verts, mesh, meshVerticesGetProperty);
			il2cpp_utils::RunMethod(&data.colors, mesh, meshColorsGetProperty);

			chunkData.Add(data);
		}



		//for (auto c : j)
		//{
		//	size_t trisSize = c["tris"].size();
		//	size_t vertsSize = c["verts"].size();
		//	size_t colorsSize = c["colors"].size();
		//	size_t meshSizesSize = c["meshSizes"].size();
		//	LOG("tris size %u, verts size %u, colors size %u, meshSizes size %u\n", trisSize, vertsSize, colorsSize, meshSizesSize);
		//	
		//	//Allocate arrays and assign them
		//	Array<Vector3>* verts = reinterpret_cast<Array<Vector3>*>(il2cpp_functions::array_new(
		//		il2cpp_utils::GetClassFromName("UnityEngine", "Vector3"), vertsSize));
		//	for (size_t i = 0; i < vertsSize; i++)
		//	{
		//		verts->values[i] = c["verts"].at(i);
		//	}

		//	Array<int32_t>* tris = reinterpret_cast<Array<int32_t>*>(il2cpp_functions::array_new(
		//		il2cpp_utils::GetClassFromName("System", "Int32"), trisSize));
		//	for (size_t i = 0; i < trisSize; i++)
		//	{
		//		tris->values[i] = c["tris"].at(i);
		//	}

		//	Array<int32_t>* meshSizes = reinterpret_cast<Array<int32_t>*>(il2cpp_functions::array_new(
		//		il2cpp_utils::GetClassFromName("System", "Int32"), meshSizesSize));
		//	for (size_t i = 0; i < meshSizesSize; i++)
		//	{
		//		meshSizes->values[i] = c["meshSizes"].at(i);
		//	}

		//	Array<Color>* colors = reinterpret_cast<Array<Color>*>(il2cpp_functions::array_new(
		//		il2cpp_utils::GetClassFromName("UnityEngine", "Color"), colorsSize));
		//	for (size_t i = 0; i < colorsSize; i++)
		//	{
		//		colors->values[i] = c["colors"].at(i);
		//	}


		//	//Il2CppObject* mesh = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine", "Mesh"));
		//	//il2cpp_utils::RunMethod(mesh, ".ctor");
		//	//il2cpp_utils::RunMethod(mesh, meshVerticesSetProperty, verts);
		//	//il2cpp_utils::RunMethod(mesh, meshColorsSetProperty, colors);
		//	//il2cpp_utils::RunMethod(mesh, meshTrianglesSetProperty, tris);


		//	ChunkMeshSlice slice;
		//	slice.z = c["id"]["z"];
		//	slice.meshSizes = nullptr;
		//	slice.tris = tris;
		//	slice.colors = colors;
		//	slice.verts = verts;

		//	chunkSlices.Add(slice);


		//	ChunkMeshData data;
		//	data.id = c["id"].get<Vector3i>();
		//	data.meshSizes = nullptr;
		//	data.tris = tris;
		//	data.colors = colors;
		//	data.verts = verts;
		//	chunkData.Add(data);
		//}	
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