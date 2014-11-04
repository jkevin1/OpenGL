#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "mesh.h"
#include "shader.h"

GLuint vao;
GLuint vbo, ibo;
float rot;
GLuint viewPosID, lightPosID;

Mesh* mesh = nullptr;
Shader* shader = nullptr;

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

GLuint modelID;
GLuint viewID;
GLuint projectionID;

glm::vec3 viewPos = glm::vec3(4.0f, 3.0f, 3.0f);
glm::mat4 projection = glm::perspective(glm::quarter_pi<float>(), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 model = glm::mat4(1.0f);

void init() {
	mesh = Mesh::sphere(2.0f, 64, 32);
	shader = new Shader("res\\vert.glsl", "res\\frag.glsl");
	shader->use();
	modelID = shader->getUniform("model"); 
	viewID = shader->getUniform("view");
	projectionID = shader->getUniform("projection");
	viewPosID = shader->getUniform("viewPos");
	lightPosID = shader->getUniform("lightPos");

	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniform3fv(viewPosID, 1, glm::value_ptr(viewPos));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Mesh::Triangle) * mesh->numTri, mesh->triangles, GL_STATIC_DRAW);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rot += glm::pi<float>() / 128;
	if (rot > 2 * glm::pi<float>()) rot -= 2 * glm::pi<float>();

	glm::vec3 lightPos = glm::vec3(10.0f * glm::cos(rot), 3.0f, 10.0f * glm::sin(rot));
	glUniform3fv(lightPosID, 1, glm::value_ptr(lightPos));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)sizeof(Vec3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, mesh->numTri*3, GL_UNSIGNED_INT, (void*)0);	
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