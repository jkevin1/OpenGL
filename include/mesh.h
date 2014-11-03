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

	const unsigned numVert, numInd;
	Vertex* vertices;
	Index* indices;

	Mesh(unsigned numVertices, unsigned numIndices);
	~Mesh();

	static Mesh* sphere(float radius, unsigned r, unsigned c);
};

#endif //MESH_H