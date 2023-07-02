#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::SetPosition(const glm::vec3& _position)
{
	m_Position = _position;
}

void Transform::SetRotation(const glm::quat& _rotation)
{
	m_Rotation = _rotation;
}

void Transform::SetScale(const glm::vec3& _scale)
{
	m_Scale = _scale;
}

void Transform::Translate(const glm::vec3& _translation)
{
	m_Position += _translation;
}

void Transform::Rotate(const glm::quat& _rotation)
{
	m_Rotation *= _rotation;
}

void Transform::Scale(const glm::vec3& _scale)
{
	m_Scale *= _scale;
}

glm::mat4 Transform::GetModel() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 rotationMatrix = glm::mat4_cast(m_Rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
	return translationMatrix * rotationMatrix * scaleMatrix;
}
