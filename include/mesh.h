#ifndef MESH_H
#define MESH_H

#include "vec3.h"

class Mesh {
public:
	struct Triangle {
		unsigned a, b, c;
	};
	struct Vertex {
		Vec3 position;
		Vec3 normal;
	};

	const unsigned numVert, numTri;
	Vertex* vertices;
	Triangle* triangles;

	Mesh(unsigned numVertices, unsigned numTriangles);
	~Mesh();

	static Mesh* sphere(float radius, unsigned rows, unsigned columns);
};

#endif //MESH_H