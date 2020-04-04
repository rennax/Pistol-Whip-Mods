#ifndef MESH_HPP
#define MESH_HPP

#include "il2cpp_utils.hpp"
#include <vector>

class Mesh {
public:
	Mesh();
	Mesh(Il2CppObject* instance);
	bool Clear();
	bool SetVertices(const std::vector<Vector3>& vertices);
	bool SetVertices(Il2CppArray* vertices);
	bool SetTriangles(const std::vector<int>& triangles);
	bool SetTriangles(Il2CppArray* triangles);
	Il2CppObject* GetMesh();
//private:
	Il2CppObject* mesh = nullptr;
	Il2CppArray* verts = nullptr;
	Il2CppArray* tris = nullptr;
};


struct Vector3i {
	int32_t x;
	int32_t y;
	int32_t z;
	
	static Vector3i* New(int32_t x, int32_t y, int32_t z)
	{
		auto klass = il2cpp_utils::GetClassFromName("", "Vector3i");
		Il2CppObject* obj = il2cpp_functions::object_new(klass);
		auto ctor = il2cpp_utils::GetMethod(klass, ".ctor", 3);
		il2cpp_utils::RunMethod(obj, ctor, &x, &y, &z);
		return (Vector3i*)il2cpp_functions::object_unbox(obj);
	}
};

typedef struct ChunkMeshData {
	Vector3i id = {0,0,0};
	Il2CppArray* verts = nullptr;
	Il2CppArray* meshSizes = nullptr;
	Il2CppArray* tris = nullptr;
	Il2CppObject* m_liveMesh = nullptr;
} ChunkMeshData;


typedef struct ChunkMeshSlice {
	int32_t z = 0;
	Il2CppArray* verts = nullptr;
	Il2CppArray* meshSizes = nullptr;
	Il2CppArray* tris = nullptr;
	Il2CppObject* m_liveMesh = nullptr;
} ChunkMeshSlice;

#endif // !MESH_HPP