#define _CRT_SECURE_NO_WARNINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Model.h"
#include "shader.h"
#include "Loader.h"
#include "Entity.h"

//glm::mat4 lookAt = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

//glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

glm::mat4 lookAt = glm::mat4(1.0f);

glm::mat4 perspective = glm::mat4(1.0f);

vector<char*> paths;

vector<Entity> entities;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void renderLoop(GLFWwindow* window, Shader* shader, vector<Entity> entities);

void loadPaths(const char* paths_path);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "NewWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	loadPaths("paths.txt");

	Shader* shader = new Shader("vertex.glsl", "fragment.glsl");

	//Shader* lampShader = new Shader("light_vertex.glsl", "light_fragment.glsl");

	//Loader* loader = new Loader(paths);

	entities.push_back(Entity(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), paths.back()));

	//lookAt = glm::translate(lookAt, glm::vec3(0.0f, 0.0f, 5.0f));

	while (!glfwWindowShouldClose(window))
	{
		renderLoop(window, shader, entities);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	/*if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(false);*/
}

void renderLoop(GLFWwindow * window, Shader * shader, vector<Entity> entities)
{
	processInput(window);

	for (Entity entity : entities)
	{
		entity.Draw(*shader, lookAt, perspective);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void loadPaths(const char * paths_path)
{
	std::ifstream pathsFile;
	std::string line;
	//char* path;

	//pathsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		pathsFile.open(paths_path);
		while (std::getline(pathsFile, line))
		{
			char * path = new char[line.size() + 1];
			strcpy(path, line.c_str());
			paths.push_back(path);
		}
		pathsFile.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to load paths " << e.what() << std::endl;
	}
}
