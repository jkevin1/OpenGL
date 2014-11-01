#include "mesh.h"


Mesh::Mesh(unsigned numVertices, unsigned numIndices) {
	vertices = new Vertex[numVertices];
	indices = new Index[numIndices];
}

Mesh::~Mesh() {
	delete[] vertices;
	delete[] indices;
}

static Mesh* sphere(int r, int c) {

}