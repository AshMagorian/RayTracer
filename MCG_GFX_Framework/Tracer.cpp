#include "Tracer.h"

#include "Ray.h"
#include "HittableObject.h"
#include "Material.h"

glm::vec3 Tracer::ColourPixel(Ray& _r, std::shared_ptr<HittableObject> _world, int _depth)
{
	HitRecord rec;
	if (_world->Hit(_r, 0.001f, 999999.00f, rec))
	{
		Ray scattered;
		glm::vec3 attenuation;

		glm::vec3 emitted = rec.mat->Emitted();

		//Checks that the number of reflections for a single ray hasn't exceeded the desired amount
		if (_depth < m_depthMax && rec.mat->Scatter(_r, rec, attenuation, scattered))
		{
			// Attenuation is the light which the object absorbs (Which gives it colour). This vec3 is multiplied by the colour calculated from the reflected ray
			return emitted + attenuation * ColourPixel(scattered, _world, _depth + 1);
		}
		else { return emitted; }
	}
	else
	{
		if (m_scene == 1)
		{
			// normalizes the ray direction
			glm::vec3 unitDirection = glm::normalize(_r.GetDirection());
			// scales t between 0 and 1
			float t = 0.5f* (unitDirection.y + 1.0f);
			//Uses lerping to give a gradient based on the value t
			return ((1.0f - t) *glm::vec3(1.0f, 1.0f, 1.0f)) + (t * glm::vec3(0.5f, 0.7f, 1.0f));
		}

		return glm::vec3(0.0f, 0.0f, 0.0f);

	}
}
