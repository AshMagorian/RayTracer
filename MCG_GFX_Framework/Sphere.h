#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include <memory>
#include "HittableObject.h"

class Sphere : public HittableObject
{
public:
	Sphere() {}
	Sphere(glm::vec3 _centre, float _radius, std::shared_ptr<Material> _mat);
	~Sphere() {}
	virtual bool Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec);
private:
	glm::vec3 m_centre;
	float m_radius;

	std::shared_ptr<Material> m_mat;
};



#endif