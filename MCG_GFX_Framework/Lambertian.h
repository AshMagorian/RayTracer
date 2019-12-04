#pragma once

#include "Material.h"


class Lambertian : public Material
{
public: 
	Lambertian(glm::vec3 _albedo) : m_albedo(_albedo) {}

	// Returns a random point inside of a unit radius sphere
	glm::vec3 RandomInUnitSphere();
	
	bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered);

private:
	// How much light is reflected
	glm::vec3 m_albedo; 
};
