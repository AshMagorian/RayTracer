#include "Box.h"

Box::Box(glm::vec3 _centrePoint, float _x, float _y, float _z, std::shared_ptr<Material> _mat)
{
	m_centrePoint = _centrePoint;

	m_B0x = m_centrePoint.x - (_x / 2);
	m_B1x = m_centrePoint.x + (_x / 2);
	
	m_B0y = m_centrePoint.y - (_y / 2);
	m_B1y = m_centrePoint.y + (_y / 2);

	m_B0z = m_centrePoint.z - (_z / 2);
	m_B1z = m_centrePoint.z + (_z / 2);

	m_mat = _mat;
}

bool Box::Hit(Ray& _r, float _tmin, float _tmax, HitRecord& _rec)
{
	//we need the largest tmin and the smallest tmax
	bool isHit = false;

	bool xSwapped = false;
	bool ySwapped = false;
	bool zSwapped = false;

	float tmin = (m_B0x - _r.GetOrigin().x) / _r.GetDirection().x;
	float tmax = (m_B1x - _r.GetOrigin().x) / _r.GetDirection().x;

	if (tmin > tmax) { std::swap(tmin, tmax); xSwapped = true; }

	float tmin_y = (m_B0y - _r.GetOrigin().y) / _r.GetDirection().y;
	float tmax_y = (m_B1y - _r.GetOrigin().y) / _r.GetDirection().y;

	if (tmin_y > tmax_y) { std::swap(tmin_y, tmax_y); ySwapped = true; }

	if ((tmin > tmax_y) || (tmin_y > tmax)) return false;

	if (tmin_y > tmin)
	{
		// if true, hits m_B0y (if ySwapped is true then hits m_B1y)
		tmin = tmin_y;  
		if (ySwapped = false)
		{
			// hits m_B0y
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(0.0f, -1.0f, 0.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
		else
		{
			//hits m_B1y
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(0.0f, 1.0f, 0.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
	}
	else
	{
		// if false, hits m_B0x (if xswapped is true then hits m_B1x)
		if (xSwapped = false)
		{
			//Hits m_B0x
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(1.0f, 0.0f, 0.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
		else
		{
			//Hits m_B1x
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
	}

	if (tmax_y < tmax) 
	{
		// if true, hits m_B1y (if ySwapped is true then his m_B0y)
		tmax = tmax_y;
		//if (ySwapped = false)
		//{
		//	// hits m_B1y
		//}
		//else
		//{
		//	//hits m_B0y
		//}
	}
	//else
	//{
	//	// if false, hits m_B1x (if xswapped is true then hits m_B0x)
	//	if (xSwapped = false)
	//	{
	//		//Hits m_B1x
	//	}
	//	else
	//	{
	//		//Hits m_B0x
	//	}
	//}

	float tmin_z = (m_B0z - _r.GetOrigin().z) / _r.GetDirection().z;
	float tmax_z = (m_B1z - _r.GetOrigin().z) / _r.GetDirection().z;

	if (tmin_z > tmax_z) { std::swap(tmin_z, tmax_z); zSwapped = true; }

	if ((tmin > tmax_z) || (tmin_z > tmax)) return false;

	if (tmin_z > tmin) 
	{
		// if true, hits m_B0z (if zSwapped is true then hits m_B1z)
		tmin = tmin_z;
		if (zSwapped = false)
		{
			// hits m_B0z
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(0.0f, 0.0f, -1.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
		else
		{
			//hits m_B1z
			if (tmin < _tmax && tmin > _tmin)
			{
				_rec.t = tmin;
				_rec.p = _r.PointAtParameter(_rec.t);
				_rec.normal = glm::vec3(0.0f, 0.0f, 1.0f);
				_rec.mat = m_mat;
				isHit = true;
			}
		}
	}
	if (tmax_z < tmax) 
	{
		// if true, hits m_B1z (if zSwapped is true then hits m_B0z)
		tmax = tmax_z; 
		//if (zSwapped = false)
		//{
		//	// hits m_B1z
		//}
		//else
		//{
		//	//hits m_B0z
		//}
	}
	if (isHit)
	{
		return true;
	}
	return false;
}