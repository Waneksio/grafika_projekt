#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

class Entity
{
public:
	glm::vec3 mPosition;
	glm::vec3 mCentralPoint;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 mDirection;
	glm::mat4 transformMatrix;
	unsigned int transformLoc;
	Entity(glm::vec3 position, glm::vec3 centralPoint, char* modelPath);
	void MoveForward(float speed);
	void MoveAside(float speed, bool direction);
	void Draw(Shader shader, glm::mat4 lookAt, glm::mat4 perspective);
private:
	Model *model;
};

#endif