#include "CCamera.h"

CCamera::CCamera():
	_position(glm::vec3(0.0f, 0.0f, 3.0f)),
	_target(glm::vec3(0.0f, 0.0f, 0.0f)),
	_up(glm::vec3(0.0f,1.0f,0.0f))
{
}

CCamera::CCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up):
	_position(position),
	_target(target),
	_up(up)
{
}

glm::mat4 CCamera::getViewMatrix() const
{
	return glm::lookAt(_position, _target, _up);
}

void CCamera::move(float distance)
{
	glm::vec3 offset = glm::normalize(_target - _position);
	offset *= distance;
	_position += offset;
	_target += offset;
}

void CCamera::rotate(float angle)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(glm::normalize(_target - _position), 0.0f);
	_target = _position + glm::vec3(rotatedViewVector.x, rotatedViewVector.y, rotatedViewVector.z);
}
