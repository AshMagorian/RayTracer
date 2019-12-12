#pragma once
#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H
#include <memory>
#include "MCG_GFX_Lib.h"
#include "Ray.h"

class Material;

struct HitRecord
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	std::shared_ptr<Material> mat;
};

class HittableObject
{
public:

	virtual void SetupObjects() {}

	virtual bool Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec) { return 0; }
};

#endif 
