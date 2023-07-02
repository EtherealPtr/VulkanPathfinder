#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
	Transform() :
		m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
		m_Scale(glm::vec3(1.0f))
	{}

	void SetPosition(const glm::vec3& _position);
	void SetRotation(const glm::quat& _rotation);
	void SetScale(const glm::vec3& _scale);

	void Translate(const glm::vec3& _translation);
	void Rotate(const glm::quat& _rotation);
	void Scale(const glm::vec3& _scale);

	glm::mat4 GetModel() const;
	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetScale() const { return m_Scale; }

private:
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;
};
