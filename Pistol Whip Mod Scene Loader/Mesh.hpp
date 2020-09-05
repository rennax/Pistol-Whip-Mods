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

typedef struct ChunkMeshData {
	Vector3i id = {0,0,0};
	Il2CppArray* verts = nullptr;
	Il2CppArray* meshSizes = nullptr;
	Il2CppArray* tris = nullptr;
	Il2CppArray* colors = nullptr;
	Il2CppObject* m_liveMesh = nullptr;
} ChunkMeshData;


typedef struct ChunkMeshSlice {
	int32_t z = 0;
	Il2CppArray* verts = nullptr;
	Il2CppArray* meshSizes = nullptr;
	Il2CppArray* tris = nullptr;
	Il2CppObject* m_liveMesh = nullptr;
	Il2CppArray* colors = nullptr;
} ChunkMeshSlice;

#endif // !MESH_HPP