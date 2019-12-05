#include "Dielectric.h"

#include <cstdlib>
#include <ctime>

bool Dielectric::Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered)
{
	glm::vec3 outwardNormal;
	glm::vec3 reflected = Reflect(_r_input.GetDirection(), _rec.normal);
	float ni_over_nt;
	_attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 refracted;

	float reflect_prob;
	float cosine;

	if (glm::dot(_r_input.GetDirection(), _rec.normal) > 0.0f)
	{
		outwardNormal = -_rec.normal;
		ni_over_nt = ref_idx;

		cosine = ref_idx * glm::dot(_r_input.GetDirection(), _rec.normal) / glm::length(_r_input.GetDirection());
	}
	else
	{
		outwardNormal = _rec.normal;
		ni_over_nt = 1.0f / ref_idx;

		cosine = -glm::dot(_r_input.GetDirection(), _rec.normal) / glm::length(_r_input.GetDirection());
	}

	if (Refract(_r_input.GetDirection(), outwardNormal, ni_over_nt, refracted))
	{
		reflect_prob = Schlick(cosine, ref_idx);
	}
	else
	{
		_r_scattered = Ray(_rec.p, reflected);
		reflect_prob = 1.0f;
	}

	//Random float betwen 0.0f and 1.0f
	float rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
	if (rndm < reflect_prob)
	{
		_r_scattered = Ray(_rec.p, reflected);
	}
	else
	{
		_r_scattered = Ray(_rec.p, refracted);
	}

	return true;

}

float Dielectric::Schlick(float cosine, float ref_idx)
{
	float r0 = (1.0f - ref_idx) / (1.0f+ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)* glm::pow((1.0f - cosine),5);
}