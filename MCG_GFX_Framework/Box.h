#pragma once
#ifndef BOX_H
#define BOX_H
#include <memory>
#include "HittableObject.h"

class Box : public HittableObject
{
public:
	Box() {}
	Box(glm::vec3 _centrePoint, float _x, float _y, float _z, std::shared_ptr<Material> _mat);
	~Box() {}
	virtual bool Hit(Ray& _r, float _tmin, float _tmax, HitRecord& _rec);

private:
	glm::vec3 m_centrePoint;
	float m_B0x;
	float m_B1x;
	float m_B0y;
	float m_B1y;
	float m_B0z;
	float m_B1z;

	std::shared_ptr<Material> m_mat;

};
#endif