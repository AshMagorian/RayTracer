#pragma once
#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H
#include <memory>
#include "MCG_GFX_Lib.h"
#include "Ray.h"

class Material;

struct HitRecord
{
	float t; // How far along the ray 
	glm::vec3 p; // Collision point
	glm::vec3 normal; // contact normal
	std::shared_ptr<Material> mat; // Material of the hit object
};

class HittableObject
{
public:

	virtual void SetupObjects(int _scene) {}

	virtual bool Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec) { return 0; }
};

#endif 
