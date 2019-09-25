#include "Entity.h"

Entity::Entity(glm::vec3 position, glm::vec3 centralPoint, char* modelPath)
{
	mPosition = position;
	mCentralPoint = centralPoint;
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	rightVector = glm::normalize(glm::cross(mCentralPoint, upVector));
	mDirection = glm::normalize(mPosition - mCentralPoint);
	mDirection = glm::normalize(glm::vec3(mDirection.x, 0.0f, mDirection.z));
	model = new Model(modelPath);
}

void Entity::MoveForward(float speed)
{
	mPosition += speed * mDirection;
}

void Entity::MoveAside(float speed, bool direction)
{
	if (direction == false)
		mPosition += glm::normalize(glm::cross(mDirection, upVector)) * speed;
	else
		mPosition -= glm::normalize(glm::cross(mDirection, upVector)) * speed;
}

void Entity::Draw(Shader shader, glm::mat4 lookAt, glm::mat4 perspective)
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f));
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));

	//transformMatrix = perspective * lookAt * modelMatrix;

	transformLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(perspective));

	transformLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lookAt));

	transformLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	model->Draw(shader);
}