#include "mesh.h"
#define _USE_MATH_DEFINES	//for M_PI
#include <math.h>

Mesh::Mesh(unsigned numVertices, unsigned numIndices) : numVert(numVertices), numInd(numIndices) {
	vertices = new Vertex[numVertices];
	indices = new Index[numIndices];
}

Mesh::~Mesh() {
	delete[] vertices;
	delete[] indices;
}

//Transposed Marc Olano's code to generate a sphere with normals
Mesh* Mesh::sphere(float radius, unsigned w, unsigned h) {
	Mesh* mesh = new Mesh((w + 1) * (h + 1), 3 * 2 * w * h);
	
	for (unsigned int j = 0, idx = 0; j <= h; ++j) {
		for (unsigned int i = 0; i <= w; ++idx, ++i) {
			// 0-1 texture coordinates from grid location

			// 3D position and normal from spherical coordinates
			float theta = float(i) / float(w)*(2.f*float(M_PI));
			float phi = float(j) / float(h)*float(M_PI);
			float cost = cosf(theta), sint = sinf(theta);
			float cosp = cosf(phi), sinp = sinf(phi);
			mesh->vertices[idx].normal = Vec3(cost*sinp, sint*sinp, cosp);
			mesh->vertices[idx].position = mesh->vertices[idx].normal * radius;
		}
	}

	// build index array linking sets of three vertices into triangles
	// two triangles per square in the grid. Each vertex index is
	// essentially its unfolded grid array position. Be careful that
	// each triangle ends up in counter-clockwise order
	for (unsigned int y = 0, idx = 0; y<h; ++y) {
		for (unsigned int x = 0; x<w; ++x) {
			mesh->indices[idx++] = (w + 1)* y + x;
			mesh->indices[idx++] = (w + 1)* y + x + 1;
			mesh->indices[idx++] = (w + 1)*(y + 1) + x + 1;

			mesh->indices[idx++] = (w + 1)* y + x;
			mesh->indices[idx++] = (w + 1)*(y + 1) + x + 1;
			mesh->indices[idx++] = (w + 1)*(y + 1) + x;
		}
	}

	return mesh;
}