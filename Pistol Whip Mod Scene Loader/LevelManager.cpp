#include "LevelManager.hpp"
#include "utils.h"
#include "il2cpp_utils.hpp"
#include "logger.h"
#include "GeoSet.hpp"
#include "Mesh.hpp"

namespace LevelManager {

	Il2CppObject* getGeoSet(Il2CppObject* gameMap)
	{
		Il2CppObject* geoSet = il2cpp_utils::GetFieldValue(gameMap, "geoSet");
		return geoSet;
	}

	

	void getGameMap(Il2CppObject* map)
	{
		if (map == nullptr)
			return;
		//Il2CppArray * gameMaps = nullptr;
		//
		//if (!il2cpp_utils::GetFieldValue(gameMaps, level, "maps"))
		//{
		//	return;
		//}
		//uint32_t mapsCount = il2cpp_functions::array_length(gameMaps);
		//LOG("\nLevelManager got gameMap from levelData\n");
		//LOG("level.maps.size = %u\n", mapsCount);
		//Il2CppObject *map;
		//map = il2cpp_array_get(gameMaps, Il2CppObject*, 0);
		LOG("\nGetting property info for map.name\n");
		const PropertyInfo* propInfo = il2cpp_functions::class_get_property_from_name(map->klass, "name");
		const MethodInfo* methodGet = propInfo->get;

		LOG("Attempting to run map.name()\n");
		//Call methodGet and print count of levels
		Il2CppString mapName;
		if (!il2cpp_utils::RunMethod(&mapName, (void*)map, methodGet))
		{
			return;
		}
		LOG("level.map.name = %s, legnth = %d\n", mapName.chars, mapName.length);
	}

	template<typename T>
	CSharp::List<T> getListField(Il2CppObject* instance, std::string_view fieldName)
	{
		Il2CppObject* fieldInstance = il2cpp_utils::GetFieldValue(instance, fieldName);
		return CSharp::List<T>(fieldInstance);
	}

	MAKE_HOOK(SpawnGeoLevel, void, Il2CppObject *level, Il2CppObject *lvlAssetDB, int minLOD)
	{
		LOG("Called LevelManager::SpawnGeoLevel() hook!\n");


		//if (level == nullptr)
		//{
		//	LOG("GameMap is null!\n");
		//	SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);
		//	return;
		//}
		////SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);

		//Il2CppObject* geoset = getGeoSet(level);
		////LOG("got geoset\n");
		////GeoSet::GeoSet geoSet(tmp);
		//CSharp::List chunkData = getListField<ChunkMeshData>(geoset, "chunkData");
		//CSharp::List chunkSlices = getListField<ChunkMeshSlice>(geoset, "chunkSlices");
		//CSharp::List staticProps = getListField<Il2CppObject*>(geoset, "staticProps");
		//CSharp::List dynamicProps = getListField<Il2CppObject*>(geoset, "dynamicProps");
		//CSharp::List decoratorCubes = getListField<Il2CppObject*>(geoset, "decoratorCubes");
		//LOG("Sizes of lists within the geoset object:\n");
		//LOG("\tchunkData = %u\n", chunkData.Count());
		//LOG("\tchunkSlices = %u\n", chunkSlices.Count());
		//LOG("\tstaticProps = %u\n", staticProps.Count());
		//LOG("\tdynamicProps = %u\n", dynamicProps.Count());
		//LOG("\tdecoratorCubes = %u\n\n", decoratorCubes.Count());

		//if (chunkSlices[0].m_liveMesh == nullptr)
		//{
		//	LOG("\tchunkSlices[0].m_liveMesh is nullptr\n");
		//}

		//LOG("Dumping size of all vertices inside chunkData objects\n");
		//for (size_t i = 0; i < chunkData.Count(); i++)
		//{
		//	ChunkMeshData chunk = chunkData[i];
		//	LOG("\tGot chunk at index %u\n", i);
		//	Il2CppArray* verts = chunk.verts;
		//	if (verts == nullptr)
		//	{
		//		LOG("Failed to get verts\n");
		//	}
		//	uint32_t length = il2cpp_functions::array_length(verts);

		//	LOG("\tChunkData at index %u, contains %u vertices\n", i, length);

		//	//if (i > 0) continue; 

		//	LOG("\n\n\tTrying to edit vertices in chunkData\n");
		//	for (size_t j = 0; j < length; j++)
		//	{
		//		GeoSet::Vector3& vec3 = il2cpp_array_get((Il2CppArray*)verts, GeoSet::Vector3, j);
		//		vec3.x *= 10;
		//		vec3.y *= 10;
		//		vec3.z *= 10;
		//		//LOG("\t\tverts[%d] = (%f, %f, %f)\n", j, vec3.x, vec3.y, vec3.z);
		//	}

		//	LOG("\n\t\tPrint vertices in chunkData.m_liveMesh to see if they have changed\n");
		//	//const PropertyInfo* meshProp = il2cpp_functions::class_get_property_from_name(chunk->klass, "mesh");
		//	Il2CppObject* mesh = chunk.m_liveMesh;
		//	//const MethodInfo* generateMesh = il2cpp_utils::GetMethod(chunk->klass, "get_mesh", 0);
		//	//LOG("\t\tSuccesful call to GetMethod()\n");
		//	//if (!il2cpp_utils::RunMethod(&mesh, chunk->klass, generateMesh))
		//	//{
		//	//	LOG("\t\tFailed to call to chunk.GenerateMesh()\n");
		//	//}
		//	if (mesh == nullptr)
		//	{
		//		LOG("\t\tmesh is nullptr\n");
		//		continue;
		//	}

		//	LOG("\t\tSuccesful call to chunk.GenerateMesh()\n");
		//	const PropertyInfo* verticesProp = il2cpp_functions::class_get_property_from_name(((Il2CppObject*)mesh)->klass, "vertices");
		//	if (verticesProp == nullptr)
		//	{
		//		LOG("\t\tverticesProp is nullptr\n");
		//		continue;
		//	}
		//	
		//	LOG("\n\t\tGot property information for vertices\n");
		//	verts = nullptr;
		//	il2cpp_utils::RunMethod(&verts, mesh, verticesProp->get);
		//	uint32_t length2 = il2cpp_functions::array_length((Il2CppArray*)verts);
		//	LOG("\t\tAt index %u, %s number of vertices\n", (length == length2 ? "same" : "not same"));
		//	for (size_t i = 0; i < length2; i++)
		//	{
		//		GeoSet::Vector3& vec3 = il2cpp_array_get((Il2CppArray*)verts, GeoSet::Vector3, i);
		//		vec3.x *= 10;
		//		vec3.y *= 10;
		//		vec3.z *= 10;
		//		LOG("\t\tverts[%d] = (%f, %f, %f)\n", i, vec3.x, vec3.y, vec3.z);
		//	}

		//	LOG("\n\n");
		//}
		//Il2CppObject* cmd = chunkData[0];
		//LOG("got cmd at index 0\n");
		//if (cmd == nullptr)
		//{
		//	LOG("Failed to get cmd item\n");
		//	SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);
		//	return;
		//}
		//Il2CppObject* verts = il2cpp_utils::GetFieldValue(cmd, "verts");
		//if (verts == nullptr)
		//{
		//	LOG("Failed to get verts\n");
		//	SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);
		//	return;
		//}
		//LOG("Got verts!\n");
		//float x = 0, y = 0, z = 0;
		//uint32_t length = il2cpp_functions::array_length((Il2CppArray*)verts);
		//LOG("Number of elements %u\n", length);
		//for (size_t i = 0; i < (length > 20 ? 20 : length); i++)
		//{
		//	GeoSet::Vector3 i0 = il2cpp_array_get((Il2CppArray*)verts, GeoSet::Vector3, i);
		//	LOG("idx%d = (%f, %f, %f)\n", i, i0.x, i0.y, i0.z);
		//}
		SpawnGeoLevel_orig(level, lvlAssetDB, minLOD);
	}

	typedef struct Mesh {

	} Mesh;

	GeoSet::GeoSet* test;
	Il2CppObject* newGeoset;
	MAKE_HOOK(LoadLevel, void, void* self, Il2CppObject* level)
	{
		LOG("Called LevelManager.LoadLevel() hook!\n");
		if (level == nullptr)
		{ 
			LOG("GameMap is null!\n");
			LoadLevel_orig(self, level);
			return;
		}		


		Il2CppObject* geoset = getGeoSet(level);

		CSharp::List chunkData = getListField<ChunkMeshData>(geoset, "chunkData");
		CSharp::List chunkSlices = getListField<ChunkMeshSlice>(geoset, "chunkSlices");
		CSharp::List staticProps = getListField<Il2CppObject*>(geoset, "staticProps");
		float scale = 0;
		il2cpp_utils::GetFieldValue(&scale, geoset, "scale");
		CSharp::List dynamicProps = getListField<Il2CppObject*>(geoset, "dynamicProps");
		CSharp::List decoratorCubes = getListField<Il2CppObject*>(geoset, "decoratorCubes");
		LOG("Sizes of lists within the geoset object:\n");
		LOG("\tScale = %f", scale);
		LOG("\tchunkData = %u\n", chunkData.Count());
		LOG("\tchunkSlices = %u\n", chunkSlices.Count());
		LOG("\tstaticProps = %u\n", staticProps.Count());
		LOG("\tdynamicProps = %u\n", dynamicProps.Count());
		LOG("\tdecoratorCubes = %u\n\n", decoratorCubes.Count());

		//Il2CppClass* klass = il2cpp_utils::GetFieldValue(geoset, "chunkData")->klass;
		//LOG("\tchunkData namespace:%s type_name: %s\n", 
		//	il2cpp_functions::class_get_namespace(klass),
		//	il2cpp_functions::class_get_name(klass)
		//	);
		//klass = il2cpp_utils::GetFieldValue(geoset, "chunkSlices")->klass;
		//LOG("\tchunkSlices namespace:%s type_name: %s\n",
		//	il2cpp_functions::class_get_namespace(klass),
		//	il2cpp_functions::class_get_name(klass)
		//	);
		//

		//ChunkMeshSlice slice = chunkSlices[0];

		/*LOG("Dumping size of all vertices inside chunkData objects\n");
		for (size_t i = 0; i < chunkData.Count(); i++)
		{
			ChunkMeshData chunk = chunkData[i];
			LOG("\tGot chunk at index %u\n", i);
			Il2CppArray* verts = chunk.verts;
			Vector3i id = chunk.id;
			LOG("\tChunkSlice id: {%d, %d, %d}", id.x, id.y, id.z);

			if (verts == nullptr) {
				LOG("Failed to get verts\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(verts);
				LOG("contains %u vertices\n", length);
			}

			Il2CppArray* meshSizes = chunk.meshSizes;
			if (meshSizes == nullptr) {
				LOG("Failed to get meshSizes\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(meshSizes);
				LOG("\tContains %u meshSizes\n", length);
			}

			Il2CppArray* tris = chunk.tris;
			if (tris == nullptr)
			{
				LOG("Failed to get tris\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(tris);
				LOG("\tContains %u tris\n\n", length);
			}

			if (chunk.m_liveMesh != nullptr)
			{
				LOG("\tContains livemesh\n\n");
			}
		}*/


		/*LOG("Dumping size of all vertices inside chunkSlices objects\n");
		for (size_t i = 0; i < chunkSlices.Count(); i++)
		{
			ChunkMeshSlice chunk = chunkSlices[i];
			LOG("\tGot chunk at index %u\n", i);
			Il2CppArray* verts = chunk.verts;
			int z = chunk.z;
			LOG("\tChunkSlice z: %d, ", z);

			if (verts == nullptr) {
				LOG("Failed to get verts\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(verts);
				LOG("contains %u vertices\n", length);
			}

			Il2CppArray* meshSizes = chunk.meshSizes;
			if (meshSizes == nullptr) {
				LOG("Failed to get meshSizes\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(meshSizes);
				LOG("\tContains %u meshSizes\n", length);
			}

			Il2CppArray* tris = chunk.tris;
			if (tris == nullptr)
			{
				LOG("Failed to get tris\n");
			}
			else {
				uint32_t length = il2cpp_functions::array_length(tris);
				LOG("\tContains %u tris\n\n", length);
			}

			if (chunk.m_liveMesh != nullptr)
			{
				LOG("\tContains livemesh\n\n");
			}
		}*/

		test = new GeoSet::GeoSet();
		test->loadVerts(test->getTestFile());
		newGeoset = test->generateGeoSet();

		////For now just copy values we aren't creating
		il2cpp_utils::SetFieldValue(newGeoset, "track", il2cpp_utils::GetFieldValue(geoset, "track"));
		Vector3i chunkSize;
		il2cpp_utils::GetFieldValue(&chunkSize, geoset, "chunkSize");
		il2cpp_utils::SetFieldValue(newGeoset, "chunkSize", &chunkSize);
		il2cpp_utils::SetFieldValue(newGeoset, "staticProps", il2cpp_utils::GetFieldValue(geoset, "staticProps"));
		il2cpp_utils::SetFieldValue(newGeoset, "dynamicProps", il2cpp_utils::GetFieldValue(geoset, "dynamicProps"));
		il2cpp_utils::SetFieldValue(newGeoset, "decoratorCubes", il2cpp_utils::GetFieldValue(geoset, "decoratorCubes"));


		il2cpp_utils::SetFieldValue(level, "geoSet", newGeoset);
		LoadLevel_orig(self, level);
	}
	
	void initHooks(funchook_t* funchookp)
	{
		LOG("LevelManager::initHooks()\n");
		SpawnGeoLevel_orig = (SpawnGeoLevel_t)il2cpp_utils::GetMethod("", "LevelManager", "SpawnLevelGeo", 3)->methodPointer;
		INSTALL_HOOK(SpawnGeoLevel);

		LoadLevel_orig = (LoadLevel_t)il2cpp_utils::GetMethod("", "LevelManager", "LoadLevel", 1)->methodPointer;
		INSTALL_HOOK(LoadLevel);
	}

};
