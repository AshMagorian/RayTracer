#include "HittableList.h"

#include "Sphere.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

void HittableList::SetupObjects()
{
	std::shared_ptr<HittableObject> one = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Lambertian>(glm::vec3(0.8f, 0.3f, 0.3f)));
	std::shared_ptr<HittableObject> two = std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_shared<Lambertian>(glm::vec3(0.9f, 0.4f, 0.0f)));
	std::shared_ptr<HittableObject> three = std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(glm::vec3(0.9f, 0.1f, 0.2f), 0.3f));
	std::shared_ptr<HittableObject> four = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Dielectric>(2.0f));
	std::shared_ptr<HittableObject> five = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -50.0f), 30.0f, std::make_shared<Metal>(glm::vec3(0.2f, 0.6f, 0.5f), 0.0f));

	m_list.emplace_back(one);
	m_list.emplace_back(two);
	m_list.emplace_back(three);
	m_list.emplace_back(four);
	m_list.emplace_back(five);
}


bool HittableList::Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec)
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = _tmax;
	for (std::list<std::shared_ptr<HittableObject>>::iterator i = m_list.begin(); i != m_list.end(); ++i)
	{
		if ((*i)->Hit(_r, _tmin, closestSoFar, tempRec))
		{
			//Confirms that the ray has hit something
			hitAnything = true;

			// Sets the hit object as the "Closest so far" for that perticular ray
			// Any closer object detected in the loop will overrite this value
			closestSoFar = tempRec.t; 

			//Stores the most recent HitRecord data
			_rec = tempRec;
		}
	}
	return hitAnything;
}