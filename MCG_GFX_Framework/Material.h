#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "HittableObject.h"

class Ray;

class Material
{
public:

	// Returns a random point inside of a unit radius sphere
	glm::vec3 RandomInUnitSphere();

	glm::vec3 Reflect(glm::vec3& _collidingRay, glm::vec3 _normal);

	bool Refract(glm::vec3 _v, glm::vec3 _n, float _ni_over_nt, glm::vec3 &_refracted);
	

	virtual bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered) { return false; }
};

#endif