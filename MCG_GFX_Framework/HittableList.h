#pragma once
#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "HittableObject.h"
#include <list>
#include <memory>

class HittableList : public HittableObject
{
public:
	HittableList() {}
	HittableList(std::list<std::shared_ptr<HittableObject>> _list, int _size) { m_list = _list; m_listSize = _size; }
	virtual bool Hit(Ray &r, float tmin, float tmax, HitRecord &rec);
private:
	std::list<std::shared_ptr<HittableObject>> m_list;
	int m_listSize;
};

bool HittableList::Hit(Ray &_r, float _tmin, float _tmax, HitRecord &_rec)
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = _tmax;
	for (std::list<std::shared_ptr<HittableObject>>::iterator i = m_list.begin(); i != m_list.end(); ++i)
	{
		if ((*i)->Hit(_r, _tmin, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			_rec = tempRec;
		}
	}
	return hitAnything;
}

#endif;