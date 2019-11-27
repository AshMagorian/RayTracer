#pragma once
#ifndef RAY_H
#define RAY_H
#include <cmath>
#include "MCG_GFX_Lib.h"

class Ray
{
public:
	Ray() {}
	Ray(glm::vec3 &_a, glm::vec3 &_b) { m_origin = _a; m_direction = _b; }
	~Ray() {}

	glm::vec3 GetOrigin() { return m_origin; }
	glm::vec3 GetDirection() { return m_direction; }
	glm::vec3 PointAtParameter(float _t) const { return m_origin + _t * m_direction; }

private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
};
#endif