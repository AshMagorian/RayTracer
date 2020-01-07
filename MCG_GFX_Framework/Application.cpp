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
#include "ThreadPool.h"

#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"


void Application::Init()
{
	glm::ivec2 windowSize(m_windowWidth, m_windowHeight);
	if (!MCG::Init(windowSize))
	{
		throw std::exception();
	}
}

int Application::Run()
{
	MCG::SetBackground(glm::ivec3(0, 0, 0));

	m_tracer = std::make_shared<Tracer>(m_depth, m_scene);
	m_cam = std::make_shared<Camera>();

	m_world = std::make_shared<HittableList>();
	m_world->SetupObjects(m_scene);

	srand(static_cast <unsigned> (time(0)));

	m_pixelCount = 0;
	m_newPixelPercent = 0.0f;
	m_oldPixelPercent = 0.0f;

	m_start = clock();

	switch (m_threadMethod)
	{
	case 1: BasicMultithreadingMethod(); break;
	case 2: ThreadPoolMethod(); break;
	default: break;
	}

	m_end = clock();
	time_elapsed = double(m_end - m_start);
	std::cout << "Time taken to render (ms): " << time_elapsed << std::endl;

	return MCG::ShowAndHold();
}

void Application::BasicMultithreadingMethod()
{
	m_blockHeight = m_windowHeight / m_numberOfThreads;

	std::list<std::thread> threads;

	for (int blockNumber = 0; blockNumber < m_numberOfThreads; blockNumber++)
	{
		threads.push_back(std::thread(&Application::DrawBlock, this, blockNumber));
	}

	for (std::list<std::thread>::iterator i = threads.begin(); i != threads.end(); ++i)
	{
		i->join();
	}
}

void Application::ThreadPoolMethod()
{
	ThreadPool pool(m_numberOfThreads);
	for (int i = 0; i < m_windowHeight; ++i)
	{
		// Adds each row individually onto the list of Tasks for the thread pool
		pool.Enqueue([=] {DrawRow(i); });
	}
}

void Application::DrawRow(int _currentPixel_y)
{

	for (int currentPixel_x = 0; currentPixel_x < m_windowWidth; currentPixel_x++)
	{
		DrawPixel(currentPixel_x, _currentPixel_y);
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
			DrawPixel(currentPixel_x, currentPixel_y);
		}
	}
	
}

void Application::DrawPixel(int _currentPixel_x, int _currentPixel_y)
{
	glm::vec3 col(0.0f, 0.0f, 0.0f);
	for (int samples = 0; samples < m_numberOfSamples; samples++)
	{
		float rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
		float rayPosX = float(_currentPixel_x + rndm) / float(m_windowWidth);
		rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
		float rayPosY = float(_currentPixel_y + rndm) / float(m_windowHeight);

		Ray r = m_cam->GetRay(rayPosX, rayPosY);
		glm::vec3 p = r.PointAtParameter(2.0f);
		col += m_tracer->ColourPixel(r, m_world, 0);
	}

	col /= float(m_numberOfSamples);
	col = glm::vec3(glm::sqrt(col.x), glm::sqrt(col.y), glm::sqrt(col.z));

	int ir = int(255.99f * col[0]);
	int ig = int(255.99f * col[1]);
	int ib = int(255.99f * col[2]);

	glm::ivec2 pixelPosition = glm::vec2(_currentPixel_x, _currentPixel_y);
	glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

	{
		std::lock_guard<std::mutex>lock{ mtx };

		MCG::DrawPixel(pixelPosition, pixelColour);


		m_newPixelPercent = (float(m_pixelCount) / (float(m_windowWidth) * float(m_windowHeight)))* 100.0f;
		if (int(m_newPixelPercent) > int(m_oldPixelPercent + 9.0f))
		{
			m_end = clock();
			double old_time = time_elapsed;
			time_elapsed = double(m_end - m_start);
			std::cout << int(m_newPixelPercent) << "% \t Time elapsed(ms): " << time_elapsed << " (+ " << time_elapsed - old_time << "ms)" << std::endl;
			m_oldPixelPercent = m_newPixelPercent;
		}
		m_pixelCount++;
	}
}