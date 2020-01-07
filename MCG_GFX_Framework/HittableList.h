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

	void SetupObjects(int _scene);

	virtual bool Hit(Ray &r, float tmin, float tmax, HitRecord &rec);
private:
	std::list<std::shared_ptr<HittableObject>> m_list;
	int m_listSize;
};



#endif;