#include "Sphere.h"

Sphere::Sphere(glm::vec3 _centre, float _radius)
{
	m_centre = _centre;
	m_radius = _radius;
}

bool Sphere::Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec)
{
	glm::vec3 oc = _r.GetOrigin() - m_centre; // A - C
	float a = glm::dot(_r.GetDirection(), _r.GetDirection()); // finding the a, b and c values for (b*b-4ac) equation (the discriminant of the quadratic equation)
	float b = 2.0f * glm::dot(oc, _r.GetDirection());
	float c = glm::dot(oc, oc) - (m_radius * m_radius);
	float discriminant = (b * b) - (4.0f *a*c);
	if (discriminant > 0.0f)
	{
		float temp = (-b - glm::sqrt(discriminant)) / (2 * a);
		if (temp < _tmax && temp > _tmin)
		{
			_rec.t = temp;
			_rec.p = _r.PointAtParameter(_rec.t);
			_rec.normal = (_rec.p - m_centre) / m_radius;
			return true;
		}
		temp = (-b + glm::sqrt(discriminant)) / (2 * a);
		if (temp < _tmax && temp > _tmin)
		{
			_rec.t = temp;
			_rec.p = _r.PointAtParameter(_rec.t);
			_rec.normal = (_rec.p - m_centre) / m_radius;
			return true;
		}
	}
	
	return false;
	
}