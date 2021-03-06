#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera
{
public:
	Camera()
	{
		m_upperLeftCorner = glm::vec3(-2.0f, 1.0f, -1.0f);
		m_horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
		m_vertical = glm::vec3(0.0f, -2.0f, 0.0f);
		m_origin = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	~Camera() {}

	Ray GetRay(float _u, float _v)
	{
		return Ray(m_origin, m_upperLeftCorner + _u*m_horizontal + _v*m_vertical - m_origin);
	}

	void Move(glm::vec3 _move) { m_upperLeftCorner += _move; m_origin += _move; }

private:
	glm::vec3 m_upperLeftCorner;
	glm::vec3 m_horizontal;
	glm::vec3 m_vertical;
	glm::vec3 m_origin;
};
#endif