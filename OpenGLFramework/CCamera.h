#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class CCamera
{
public:
	CCamera();
	CCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

	glm::mat4 getViewMatrix() const;
	void move(float distance);
	void rotate(float angle);

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getTarget() const { return _target; }
	glm::vec3 getUpVector() const { return _up; }

private:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _up;

};

