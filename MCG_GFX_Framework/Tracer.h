#pragma once
#include <memory>
#include "MCG_GFX_Lib.h"

class Ray;
class HittableObject;

class Tracer
{
public:
	Tracer(int _depth, int _scene) { m_depthMax = _depth; m_scene = _scene; }
	glm::vec3 ColourPixel(Ray& _r, std::shared_ptr<HittableObject> _world, int _depth);

private:
	int m_depthMax;
	int m_scene;
};