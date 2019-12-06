#pragma once
#include <memory>
#include "MCG_GFX_Lib.h"

class Ray;
class HittableObject;

class Tracer
{
public:
	glm::vec3 ColourPixel(Ray& _r, std::shared_ptr<HittableObject> _world, int _depth);
};