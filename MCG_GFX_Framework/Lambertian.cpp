#include "Lambertian.h"

glm::vec3 Lambertian::RandomInUnitSphere()
{
	glm::vec3 rtn;
	do
	{
		//Fill the vec3 with 3 randomly generated floats ranging from -1 to 1
		rtn.x = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
		rtn.y = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
		rtn.z = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
	} while (glm::dot(rtn, rtn) >= 1.0f); //rejects if the point is located outside of the sphere
	return rtn;
}

bool Lambertian::Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered)
{
	glm::vec3 target = _rec.p + _rec.normal + RandomInUnitSphere();
	_r_scattered = Ray(_rec.p, target - _rec.p);
	_attenuation = m_albedo;
	return true;
}