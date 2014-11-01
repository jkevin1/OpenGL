#ifndef MESH_H
#define MESH_H

#include "vec3.h"

class Mesh {
public:
	typedef unsigned int Index;
	struct Vertex {
		Vec3 position;
		Vec3 normal;
	};

	Vertex* vertices;
	Index* indices;

	Mesh(unsigned numVertices, unsigned numIndices);
	~Mesh();

	static Mesh* sphere(int r, int c);
};

#endif //MESH_H