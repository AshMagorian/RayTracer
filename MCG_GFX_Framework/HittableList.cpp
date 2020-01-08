#include "HittableList.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "DiffuseLight.h"

void HittableList::SetupObjects(int _scene)
{
	//set up spheres
	m_list.emplace_back(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Lambertian>(glm::vec3(0.8f, 0.3f, 0.3f))));
	m_list.emplace_back(std::make_shared<Sphere>(glm::vec3(1.2f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(glm::vec3(0.9f, 0.1f, 0.2f), 0.3f)));
	m_list.emplace_back(std::make_shared<Sphere>(glm::vec3(-1.2f, 0.0f, -1.0f), 0.5f, std::make_shared<Dielectric>(2.0f)));
	m_list.emplace_back(std::make_shared<Sphere>(glm::vec3(-1.5f, 1.0f, -3.0f), 1.5f, std::make_shared<Metal>(glm::vec3(0.2f, 0.6f, 0.5f), 0.0f)));
	//set up cubes
	m_list.emplace_back(std::make_shared<Box>(glm::vec3(0.8f, -0.4f, -0.5f), 0.2f, 0.2f, 0.2f, std::make_shared<Metal>(glm::vec3(0.9f, 0.9f, 0.9f), 0.0f)));
	m_list.emplace_back(std::make_shared<Box>(glm::vec3(-0.5f, -0.4f, -0.5f), 0.2f, 0.2f, 0.2f, std::make_shared<Lambertian>(glm::vec3(0.1f, 0.9f, 0.3f))));
	//set up planes
	//floor
	m_list.emplace_back(std::make_shared<Plane>(glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.4f, 0.0f))));

	if (_scene == 2)
	{
		//far wall
		m_list.emplace_back(std::make_shared<Plane>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -1.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.9f, 0.9f))));
		//rear wall
		m_list.emplace_back(std::make_shared<Plane>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.9f, 0.9f))));
		//left wall
		m_list.emplace_back(std::make_shared<Plane>(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.9f, 0.9f))));
		//right wall
		m_list.emplace_back(std::make_shared<Plane>(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.9f, 0.9f))));
		//ceiling
		m_list.emplace_back(std::make_shared<Plane>(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), std::make_shared<Lambertian>(glm::vec3(0.9f, 0.4f, 0.0f))));
		//set up light
		m_list.emplace_back(std::make_shared<Sphere>(glm::vec3(0.0f, 2.5f, -1.0f), 0.4f, std::make_shared<DiffuseLight>(glm::vec3(4.0f, 4.0f, 4.0f))));
		m_list.emplace_back(std::make_shared<Box>(glm::vec3(1.5f, -0.4f, -0.5f), 0.2f, 0.2f, 0.1f, std::make_shared<DiffuseLight>(glm::vec3(2.0f, 2.0f, 2.0f))));
	}
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