
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MCG_GFX_Lib.h"
#include "Sphere.h"
#include "HittableList.h"
#include "float.h"
#include "Camera.h"

glm::vec3 RandomInUnitSphere();
glm::vec3 Colour(Ray& _r, std::shared_ptr<HittableObject> _world);


int main( int argc, char *argv[] )
{
	int windowWidth = 600;
	int windowHeight = 300;
	int numberOfSamples = 10;

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

	std::shared_ptr<HittableObject> one = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
	std::shared_ptr<HittableObject> two = std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f);

	objectList.emplace_back(one);
	objectList.emplace_back(two);
	std::shared_ptr<HittableObject> world = std::make_shared<HittableList>(objectList, 2);

	srand(static_cast <unsigned> (time(0)));

	Camera cam;

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
				col += Colour(r, world);
			}
			
			col /= float(numberOfSamples);
			col = glm::vec3(glm::sqrt(col.x), glm::sqrt(col.y), glm::sqrt(col.z));

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			glm::ivec2 pixelPosition = glm::vec2(i, j);
			glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

			MCG::DrawPixel(pixelPosition, pixelColour);
			
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

glm::vec3 RandomInUnitSphere()
{
	glm::vec3 rtn;
	do
	{
		rtn.x = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
		rtn.y = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
		rtn.z = (-1.0f) + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
	} while (glm::dot(rtn, rtn) >= 1.0f);
	return rtn;
}

glm::vec3 Colour(Ray& _r, std::shared_ptr<HittableObject> _world)
{
	HitRecord rec;
	if (_world->Hit(_r, 0.001f, 999999.00f, rec))
	{
		// Scales each unit between 0 and 1
		//return 0.5f*glm::vec3((rec.normal.x) + 1.0f, (rec.normal.y) + 1.0f, (rec.normal.z) + 1.0f); 
		glm::vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		return 0.5f * Colour(Ray(rec.p, target - rec.p), _world);
	}
	else
	{
		// normalizes the ray direction
		glm::vec3 unitDirection = glm::normalize(_r.GetDirection());
		// scales t between 0 and 1
		float t = 0.5f* (unitDirection.y + 1.0f);
		//Uses lerping to give a gradient based on the value t
		return ((1.0f - t) *glm::vec3(1.0f, 1.0f, 1.0f)) + (t * glm::vec3(0.5f, 0.7f, 1.0f));
	}
}