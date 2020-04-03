#ifndef MESH_HPP
#define MESH_HPP

#include "il2cpp_utils.hpp"
#include <vector>

class Mesh {
public:
	Mesh();
	Mesh(Il2CppObject* instance);
	bool Clear();
	bool SetVertices(std::vector<Vector3> vertices);
	bool SetVertices(Il2CppArray* vertices);
	bool SetTriangles(std::vector<int> triangles);
	bool SetTriangles(Il2CppArray* triangles);
	Il2CppObject* GetMesh();
private:
	Il2CppObject* mesh = nullptr;
	Il2CppArray* verts = nullptr;
	Il2CppArray* tris = nullptr;
};


struct Vector3i {
	int32_t x;
	int32_t y;
	int32_t z;
};

typedef struct ChunkMeshData {
	Vector3i id;
	Il2CppArray* verts;
	Il2CppArray* meshSizes;
	Il2CppArray* tris;
	Il2CppObject* m_liveMesh;
} ChunkMeshData;


typedef struct ChunkMeshSlice {
	int32_t z;
	Il2CppArray* verts;
	Il2CppArray* meshSizes;
	Il2CppArray* tris;
	Il2CppObject* m_liveMesh;
} ChunkMeshSlice;

#endif // !MESH_HPP