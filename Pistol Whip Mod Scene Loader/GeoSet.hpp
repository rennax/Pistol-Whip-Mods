#ifndef GEOSET_HPP
#define GEOSET_HPP
extern "C" {
#include "funchook.h"
}

#include "il2cpp_utils.hpp"
#include "List.hpp"
#include "logger.h"

namespace GeoSet {
	using namespace CSharp;

	typedef struct Vector3 {
		float x;
		float y;
		float z;
	} Vector3;

	struct GeoSet {
		GeoSet(Il2CppObject* instance)
		{
			track = il2cpp_utils::GetFieldValue(instance, "track");
			chunkSize = il2cpp_utils::GetFieldValue(instance, "chunkSize");
			il2cpp_utils::GetFieldValue(&scale, instance, "scale");
		}
		bool construct(Il2CppObject* instance) {
			LOG("Constructing GeoSet Object \n");
			Il2CppObject* tmp = nullptr;

			//if (!il2cpp_utils::GetFieldValue(tmp, instance, "chunkData"))
			//	return false;
			//chunkData = List(tmp);
			//if (!il2cpp_utils::GetFieldValue(tmp, instance, "chunkSlices"))
			//	return false;
			//chunkSlices = List(tmp);
			//if (!il2cpp_utils::GetFieldValue(tmp, instance, "staticProps"))
			//	return false;
			//staticProps = List(tmp);
			//if (!il2cpp_utils::GetFieldValue(tmp, instance, "dynamicProps"))
			//	return false;
			//dynamicProps = List(tmp);
			//if (!il2cpp_utils::GetFieldValue(tmp, instance, "decoratorCubes"))
			//	return false;
			//decoratorCubes = List(tmp);
		}
		Il2CppObject* track = nullptr; //Track
		Il2CppObject* chunkSize = nullptr; //Vector3i
		float scale = 0; 
		//List chunkData; // ChunkMeshData
		//List chunkSlices; // ChunkMeshSlice
		//List staticProps; // WorldObject
		//List dynamicProps; // WorldObject
		//List decoratorCubes; // OscillatingObjectData
	};
};

#endif // !GEOSET_HPP
