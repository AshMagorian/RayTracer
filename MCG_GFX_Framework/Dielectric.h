#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float _ri) : ref_idx(_ri) {}

	bool Scatter(Ray &_r_input, HitRecord &_rec, glm::vec3 &_attenuation, Ray &_r_scattered);
	
	//Function by Christopher Schlick which calculates mirror qualities of glass when viewed at a narrow angle
	float Schlick(float cosine, float ref_idx);

private:
	float ref_idx;
};