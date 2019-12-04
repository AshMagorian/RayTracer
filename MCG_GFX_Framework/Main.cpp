
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MCG_GFX_Lib.h"
#include "Sphere.h"
#include "HittableList.h"
#include "float.h"
#include "Camera.h"

#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"

// Returns a random point inside of a unit radius sphere
//glm::vec3 RandomInUnitSphere();

glm::vec3 Colour(Ray& _r, std::shared_ptr<HittableObject> _world, int _depth);


int main( int argc, char *argv[] )
{
	int windowWidth = 600;
	int windowHeight = 300;
	int numberOfSamples = 50;

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
	std::shared_ptr<HittableObject> three = std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(glm::vec3(0.8f, 0.6f, 0.2f)));
	std::shared_ptr<HittableObject> four = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(glm::vec3(0.8f, 0.8f, 0.8f)));

	objectList.emplace_back(one);
	objectList.emplace_back(two);
	objectList.emplace_back(three);
	objectList.emplace_back(four);
	std::shared_ptr<HittableObject> world = std::make_shared<HittableList>(objectList, 4);

	srand(static_cast <unsigned> (time(0)));

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
				col += Colour(r, world, 0);
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

	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:

	/*
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );

	}

	return 0;
	*/

}

//glm::vec3 RandomInUnitSphere()
//{
//	glm::vec3 rtn;
//	do
//	{
//		//Fill the vec3 with 3 randomly generated floats ranging from -1 to 1
//		rtn.x = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
//		rtn.y = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
//		rtn.z = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
//	} while (glm::dot(rtn, rtn) >= 1.0f); //rejects if the point is located outside of the sphere
//	return rtn;
//}

glm::vec3 Colour(Ray& _r, std::shared_ptr<HittableObject> _world, int _depth)
{
	HitRecord rec;
	if (_world->Hit(_r, 0.001f, 999999.00f, rec))
	{
		Ray scattered;
		glm::vec3 attenuation;
		if (_depth < 50 && rec.mat->Scatter(_r, rec, attenuation, scattered))
		{
			return attenuation * Colour(scattered, _world, _depth + 1);
		}
		else { return glm::vec3(0.0f, 0.0f, 0.0f); }

		//Generates random ray to simulate light reflecting off of the sphere
		//glm::vec3 target = rec.p + rec.normal + RandomInUnitSphere( );

		//Checks if that ray collides with another object. The more the ray reflects the darker the colour is (this simulates light being absorbed)
		//return 0.5f * Colour(Ray(rec.p, target - rec.p), _world);
	}
	else
	{
		// normalizes the ray direction
		glm::vec3 unitDirection = glm::normalize(_r.GetDirection());
		// scales t between 0 and 1
		float t = 0.5f* (unitDirection.y + 1.0f);
		//Uses lerping to give a gradient based on the value t
		//return ((1.0f - t) *glm::vec3(1.0f, 0.1f, 0.0f)) + (t * glm::vec3( 1.0f, 0.0f, 1.0f));
		return ((1.0f - t) *glm::vec3(1.0f, 1.0f, 1.0f)) + (t * glm::vec3(0.5f, 0.7f, 1.0f));
	}
}