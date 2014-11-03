#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "shader.h"

GLuint vao;
GLuint vbo, ibo;

Mesh* mesh = nullptr;
Shader* shader = nullptr;

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

GLuint mvpID;

glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 view = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 model = glm::mat4(1.0f);

void init() {
	mesh = Mesh::sphere(1.0f, 16, 8);
	shader = new Shader("res\\vert.glsl", "res\\frag.glsl");
	shader->use();
	mvpID = shader->getUniform("MVP");

	glViewport(0, 0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh::Vertex) * mesh->numVert, mesh->vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Mesh::Index) * mesh->numInd, mesh->indices, GL_STATIC_DRAW);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model = glm::rotate(model, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mvp = projection * view * model;
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 3, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, mesh->numInd, GL_UNSIGNED_INT, (void*)0);	
	glDisableVertexAttribArray(0);
}

void close() {
	delete mesh;
	delete shader;
}

int main(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	while (!glfwWindowShouldClose(window)) {
		render();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	close();

	glfwTerminate();
	return 0;
}