#pragma once
#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H
#include "MCG_GFX_Lib.h"
#include "Ray.h"

struct HitRecord
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

class HittableObject
{
public:
	virtual bool Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec) { return 0; }
};

#endif 
