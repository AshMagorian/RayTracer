#include "Sphere.h"

Sphere::Sphere(glm::vec3 _centre, float _radius, std::shared_ptr<Material> _mat)
{
	m_centre = _centre;
	m_radius = _radius;
	m_mat = _mat;
}

bool Sphere::Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec)
{
	glm::vec3 oc = _r.GetOrigin() - m_centre; // A - C

	// finding the a, b and c values for (b*b-4ac) equation (the discriminant of the quadratic equation)
	float a = glm::dot(_r.GetDirection(), _r.GetDirection()); 
	float b = 2.0f * glm::dot(oc, _r.GetDirection());
	float c = glm::dot(oc, oc) - (m_radius * m_radius);

	//The discriminant is the part of the quadratic equation inside the square root symbol
	float discriminant = (b * b) - (4.0f *a*c);

	//A negative discriminant means the ray does not hit the sphere
	if (discriminant > 0.0f)
	{
		_rec.mat = m_mat;

		//Calculates the first value of the quadratic equation
		float temp = (-b - glm::sqrt(discriminant)) / (2 * a);

		// Checks if it is the nearest surface to the camera
		if (temp < _tmax && temp > _tmin)
		{
			_rec.t = temp;
			_rec.p = _r.PointAtParameter(_rec.t);
			_rec.normal = (_rec.p - m_centre) / m_radius;
			return true;
		}
		
		//Calculates the second value of the quadratic equation
		temp = (-b + glm::sqrt(discriminant)) / (2 * a);

		// Checks if it is the nearest surface to the camera
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