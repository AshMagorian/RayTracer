#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(glm::vec3 &_albedo, float _fuzz) : m_albedo(_albedo), m_fuzz(_fuzz) {}

	bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered);

private:
	glm::vec3 m_albedo;
	float m_fuzz;
};