#pragma once
#ifndef DIFFUSE_LIGHT
#define DIFFUSE_LIGHT

#include "Material.h"

class DiffuseLight : public Material
{
public:

	DiffuseLight(glm::vec3 _colour) { m_colour = _colour; }

	bool Scatter(Ray& _r_input, HitRecord& _rec, glm::vec3& _attenuation, Ray& _r_scattered) { return false; }
	glm::vec3 Emitted() { return m_colour; }

private:
	glm::vec3 m_colour;

};
#endif