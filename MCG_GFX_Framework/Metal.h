#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(glm::vec3 &_albedo) : m_albedo(_albedo) {}

	glm::vec3 Reflect(glm::vec3& _collidingRay, glm::vec3 _normal);

	bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered);
private:
	glm::vec3 m_albedo;
};