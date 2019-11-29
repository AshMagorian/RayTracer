#include "HittableList.h"

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