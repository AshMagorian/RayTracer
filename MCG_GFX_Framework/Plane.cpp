#include "Plane.h"

Plane::Plane(glm::vec3 _point, glm::vec3 _normal, std::shared_ptr<Material> _mat)
{
	m_point = _point; // Any point on the plane
	m_normal = _normal; // The normal of the plane
	m_mat = _mat; // The material of the plane
}

bool Plane::Hit(Ray& _r, float _tmin, float _tmax, HitRecord& _rec)
{
	//Check against the plane equation: t = (dot(p0-l0, normal)) / (dot(l, n)) 

	//finds the value of teh denominator of the equation to make sure it isn't below zero
	float denom = glm::dot(m_normal, _r.GetDirection());
	if (denom > 0.001)
	{
		float temp = glm::dot(m_point - _r.GetOrigin(), m_normal) / denom;
		if (temp < _tmax && temp > _tmin)
		{
			_rec.mat = m_mat;
			_rec.t = temp;
			_rec.p = _r.PointAtParameter(_rec.t);
			_rec.normal = -m_normal;
			return true;
		}
	}
	return false;
}