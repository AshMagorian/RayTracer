#include "Application.h"

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <list>

#include "MCG_GFX_Lib.h"
#include "Sphere.h"
#include "HittableList.h"
#include "float.h"
#include "Camera.h"
#include "Tracer.h"

#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

void Application::Init()
{
	m_windowWidth = 1200;
	m_windowHeight = 600;
	glm::ivec2 windowSize(m_windowWidth, m_windowHeight);
	if (!MCG::Init(windowSize))
	{
		throw std::exception();
	}
}

int Application::Run()
{
	m_numberOfSamples = 100;

	MCG::SetBackground(glm::ivec3(0, 0, 0));

	m_tracer = std::make_shared<Tracer>();
	m_cam = std::make_shared<Camera>();

	m_world = std::make_shared<HittableList>();
	m_world->SetupObjects();

	srand(static_cast <unsigned> (time(0)));

	m_pixelCount = 0;
	m_newPixelPercent = 0.0f;
	m_oldPixelPercent = 0.0f;

	std::cout << std::thread::hardware_concurrency() << " cores detected";
	m_numberOfThreads = std::thread::hardware_concurrency();


	m_blockHeight = m_windowHeight / m_numberOfThreads;


	std::list<std::thread> threads;

	for (int blockNumber = 0; blockNumber < m_numberOfThreads; blockNumber++)
	{
		//DrawBlock(blockNumber);
		threads.push_back(std::thread(&Application::DrawBlock, this, blockNumber));
	}

	for (std::list<std::thread>::iterator i = threads.begin(); i != threads.end(); ++i)
	{
		i->join();
	}

	//for (m_currentPixel_y = 0; m_currentPixel_y < m_windowHeight; m_currentPixel_y++)
	//{
	//	DrawRow();
	//}

	return MCG::ShowAndHold();
}

void Application::DrawRow()
{
	for (int m_currentPixel_x = 0; m_currentPixel_x < m_windowWidth; m_currentPixel_x++)
	{
		glm::vec3 col(0.0f, 0.0f, 0.0f);
		for (int samples = 0; samples < m_numberOfSamples; samples++)
		{
			float rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
			float rayPosX = float(m_currentPixel_x + rndm) / float(m_windowWidth);
			rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
			float rayPosY = float(m_currentPixel_y + rndm) / float(m_windowHeight);

			Ray r = m_cam->GetRay(rayPosX, rayPosY);
			glm::vec3 p = r.PointAtParameter(2.0f);
			col += m_tracer->ColourPixel(r, m_world, 0);
		}

		col /= float(m_numberOfSamples);
		col = glm::vec3(glm::sqrt(col.x), glm::sqrt(col.y), glm::sqrt(col.z));

		int ir = int(255.99f * col[0]);
		int ig = int(255.99f * col[1]);
		int ib = int(255.99f * col[2]);

		glm::ivec2 pixelPosition = glm::vec2(m_currentPixel_x, m_currentPixel_y);
		glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

		MCG::DrawPixel(pixelPosition, pixelColour);

		//m_newPixelPercent = (float(m_pixelCount) / (float(m_windowWidth) * float(m_windowHeight)))* 100.0f;
		//if (int(m_newPixelPercent) > int(m_oldPixelPercent))
		//{
		//	std::cout << int(m_newPixelPercent) << "%" << std::endl;
		//}
		//m_pixelCount++;
		//m_oldPixelPercent = m_newPixelPercent;
	}
}

void Application::DrawBlock(int _blockNumber)
{
	int currentPixel_y = 0;
	for (int j = 0; j < m_blockHeight; j++)
	{
		currentPixel_y = (m_blockHeight * _blockNumber) + j;
		for (int currentPixel_x = 0; currentPixel_x < m_windowWidth; currentPixel_x++)
		{
			glm::vec3 col(0.0f, 0.0f, 0.0f);
			for (int samples = 0; samples < m_numberOfSamples; samples++)
			{
				float rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				float rayPosX = float(currentPixel_x + rndm) / float(m_windowWidth);
				rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				float rayPosY = float(currentPixel_y + rndm) / float(m_windowHeight);

				Ray r = m_cam->GetRay(rayPosX, rayPosY);
				glm::vec3 p = r.PointAtParameter(2.0f);
				col += m_tracer->ColourPixel(r, m_world, 0);
			}

			col /= float(m_numberOfSamples);
			col = glm::vec3(glm::sqrt(col.x), glm::sqrt(col.y), glm::sqrt(col.z));

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			glm::ivec2 pixelPosition = glm::vec2(currentPixel_x, currentPixel_y);
			glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

			mtx.lock();
			MCG::DrawPixel(pixelPosition, pixelColour);
			

			m_newPixelPercent = (float(m_pixelCount) / (float(m_windowWidth) * float(m_windowHeight)))* 100.0f;
			if (int(m_newPixelPercent) > int(m_oldPixelPercent))
			{
				std::cout << int(m_newPixelPercent) << "%" << std::endl;
			}
			m_pixelCount++;
			m_oldPixelPercent = m_newPixelPercent;
			mtx.unlock();
		}
	}
	
}