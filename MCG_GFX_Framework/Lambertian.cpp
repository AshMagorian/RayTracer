#include "Lambertian.h"



bool Lambertian::Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered)
{
	//Randomly generates a vector to simulate light reflecting off of the sphere
	glm::vec3 target = _rec.p + _rec.normal + RandomInUnitSphere();

	//Turns this vector into a Ray
	_r_scattered = Ray(_rec.p, target - _rec.p);

	_attenuation = m_albedo;
	return true;
}