#include "Plane.h"

Plane::Plane(glm::vec3 _point, glm::vec3 _normal, std::shared_ptr<Material> _mat)
{
	m_point = _point;
	m_normal = _normal;
	m_mat = _mat;
}

bool Plane::Hit(Ray& _r, float _tmin, float _tmax, HitRecord& _rec)
{
	float denom = glm::dot(m_normal, _r.GetDirection());
	if (denom > 0.001)
	{
		glm::vec3 a = m_point - _r.GetOrigin();
		float temp = glm::dot(a, m_normal) / denom;
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