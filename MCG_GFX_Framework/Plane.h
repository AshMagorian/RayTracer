#pragma once
#ifndef PLANE_H
#define PLANE_H
#include <memory>
#include "HittableObject.h"

class Plane : public HittableObject
{
public:
	Plane() {}
	Plane(glm::vec3 _point, glm::vec3 _normal, std::shared_ptr<Material> _mat);
	~Plane() {}
	virtual bool Hit(Ray& _r, float _tmin, float _tmax, HitRecord& _rec);

private:
	glm::vec3 m_point;
	glm::vec3 m_normal;

	std::shared_ptr<Material> m_mat;

};
#endif