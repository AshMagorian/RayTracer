#include "Metal.h"

bool Metal::Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered)
{
	glm::vec3 reflected = Reflect(glm::normalize(_r_input.GetDirection()), _rec.normal);
	_r_scattered = Ray(_rec.p, reflected + m_fuzz * RandomInUnitSphere());
	_attenuation = m_albedo;
	return (glm::dot(_r_scattered.GetDirection(), _rec.normal) > 0);

}