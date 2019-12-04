#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "HittableObject.h"

class Ray;

class Material
{
public:

	virtual bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered) { return false; }
};

#endif