#include "Metal.h"

glm::vec3 Metal::Reflect(glm::vec3& _collidingRay, glm::vec3 _normal)
{
	return _collidingRay - 2 * glm::dot(_collidingRay, _normal)* _normal;
}

bool Metal::Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered)
{
	glm::vec3 reflected = Reflect(glm::normalize(_r_input.GetDirection()), _rec.normal);
	_r_scattered = Ray(_rec.p, reflected);
	_attenuation = m_albedo;
	return (glm::dot(_r_scattered.GetDirection(), _rec.normal) > 0);

}