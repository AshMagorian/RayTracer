#include "Material.h"


glm::vec3 Material::RandomInUnitSphere()
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

glm::vec3 Material::Reflect(glm::vec3& _collidingVec, glm::vec3 _normal)
{
	return _collidingVec - 2 * glm::dot(_collidingVec, _normal)* _normal;
}

bool Material::Refract(glm::vec3 _collidingVec, glm::vec3 _normal, float _ni_over_nt, glm::vec3 &_refracted)
{
	glm::vec3 unitVec = glm::normalize(_collidingVec);
	float dt = glm::dot(unitVec, _normal);
	float discriminant = 1.0f - _ni_over_nt * _ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0)
	{
		_refracted = _ni_over_nt * (unitVec - _normal * dt) - _normal * glm::sqrt(discriminant);
		return true;
	}
	else { return false; }
}