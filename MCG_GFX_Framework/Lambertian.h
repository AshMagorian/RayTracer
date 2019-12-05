#pragma once

#include "Material.h"


class Lambertian : public Material
{
public: 
	Lambertian(glm::vec3 _albedo) : m_albedo(_albedo) {}

	
	
	bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered);

private:
	// How much light is reflected
	glm::vec3 m_albedo; 
};
