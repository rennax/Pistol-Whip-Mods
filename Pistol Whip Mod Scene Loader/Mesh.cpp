#include "Mesh.hpp"

Mesh::Mesh()
{
	auto klass = il2cpp_utils::GetClassFromName("UnityEngine", "Mesh");
	mesh = il2cpp_utils::New(klass);
}

Mesh::Mesh(Il2CppObject* instance) : mesh(instance)
{

}

bool Mesh::Clear()
{
	return il2cpp_utils::RunMethod(mesh, "Clear");
}

bool Mesh::SetVertices(const std::vector<Vector3>& vertices)
{
	size_t size = sizeof(Vector3) * vertices.size();
	verts = il2cpp_utils::CreateIl2CppArray("UnityEngine", "Vector3", size);
	for (size_t i = 0; i < vertices.size(); i++)
	{
		il2cpp_array_set(verts, Vector3, i, vertices[i]);
	}
	return SetVertices(verts);
}

bool Mesh::SetVertices(Il2CppArray* vertices)
{
	return il2cpp_utils::RunMethod(mesh, "set_vertices", vertices);
}

bool Mesh::SetTriangles(const std::vector<int>& triangles)
{
	size_t size = sizeof(int) * triangles.size();
	tris = il2cpp_utils::CreateIl2CppArray("System", "Int32", size);
	for (size_t i = 0; i < triangles.size(); i++)
	{
		il2cpp_array_set(tris, int, i, triangles[i]);
	}
	return SetTriangles(tris);
}

bool Mesh::SetTriangles(Il2CppArray* triangles)
{
	return il2cpp_utils::RunMethod(mesh, "set_triangles", triangles);
}

Il2CppObject* Mesh::GetMesh()
{
	return mesh;
}
