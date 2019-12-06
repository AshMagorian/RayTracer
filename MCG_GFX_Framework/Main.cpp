
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

int main( int argc, char *argv[] )
{
	int windowWidth = 600;
	int windowHeight = 300;
	int numberOfSamples = 10 ;

	// Variable for storing window dimensions
	glm::ivec2 windowSize( windowWidth, windowHeight);

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	MCG::SetBackground( glm::ivec3(0,0,0) );

	std::list<std::shared_ptr<HittableObject>> objectList;

	std::shared_ptr<HittableObject> one = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Lambertian>(glm::vec3(0.8f, 0.3f, 0.3f)));
	std::shared_ptr<HittableObject> two = std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_shared<Lambertian>(glm::vec3(0.8f, 0.8f, 0.0f)));
	std::shared_ptr<HittableObject> three = std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(glm::vec3(0.8f, 0.6f, 0.2f), 0.3f));
	std::shared_ptr<HittableObject> four = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Dielectric>(1.5f));


	objectList.emplace_back(one);
	objectList.emplace_back(two);
	objectList.emplace_back(three);
	objectList.emplace_back(four);
	std::shared_ptr<HittableObject> world = std::make_shared<HittableList>(objectList, 4);

	srand(static_cast <unsigned> (time(0)));

	Tracer tracer;
	Camera cam;
	int pixelCount = 0;
	float newPixelPercent = 0.0f;
	float oldPixelPercent = 0.0f;

	for (int j = 0; j < windowHeight; j++)
	{
		for (int i = 0; i < windowWidth; i++)
		{
			glm::vec3 col(0.0f, 0.0f, 0.0f);
			for (int samples = 0; samples < numberOfSamples; samples++)
			{
				float rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				float rayPosX = float(i + rndm) / float(windowWidth);
				rndm = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				float rayPosY = float(j + rndm) / float(windowHeight);

				Ray r = cam.GetRay(rayPosX, rayPosY);
				glm::vec3 p = r.PointAtParameter(2.0f);
				col += tracer.ColourPixel(r, world, 0);
			}
			
			col /= float(numberOfSamples);
			col = glm::vec3(glm::sqrt(col.x), glm::sqrt(col.y), glm::sqrt(col.z));

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			glm::ivec2 pixelPosition = glm::vec2(i, j);
			glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

			MCG::DrawPixel(pixelPosition, pixelColour);



			newPixelPercent = (float(pixelCount) / (float(windowWidth) * float(windowHeight)))* 100.0f;
			if (int(newPixelPercent) > int(oldPixelPercent))
			{
				std::cout << int(newPixelPercent) << "%" << std::endl;
			}
			pixelCount++;
			oldPixelPercent = newPixelPercent;
		}

	}

	return MCG::ShowAndHold();

}

