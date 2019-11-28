
#include <cmath>
#include <iostream>

#include "MCG_GFX_Lib.h"
#include "Sphere.h"
#include "HittableList.h"
#include "float.h"


glm::vec3 Colour(Ray& _r, std::shared_ptr<HittableObject> _world)
{
	HitRecord rec;
	if (_world->Hit(_r, 0.0f, 999999.00f, rec))
	{
		return 0.5f*glm::vec3((rec.normal.x) + 1.0f, (rec.normal.y) + 1.0f, (rec.normal.z) + 1.0f); // Scales each unit between 0 and 1
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(_r.GetDirection()); // normalizes the ray direction
		float t = 0.5f* (unitDirection.y + 1.0f); // scales t between 0 and 1

		return ((1.0f - t) *glm::vec3(1.0f, 1.0f, 1.0f)) + (t * glm::vec3(0.5f, 0.7f, 1.0f));
	}
}

int main( int argc, char *argv[] )
{
	int windowWidth = 600;
	int windowHeight = 300;

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

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground( glm::ivec3(0,0,0) );

	glm::vec3 upperLeftCorner(-2.0f, 1.0f, -1.0f);
	glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
	glm::vec3 vertical(0.0f, -2.0f, 0.0f);
	glm::vec3 origin(0.0f, 0.0f, 0.0f);

	std::list<std::shared_ptr<HittableObject>> objectList;

	std::shared_ptr<HittableObject> one = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
	std::shared_ptr<HittableObject> two = std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f);

	objectList.emplace_back(one);
	objectList.emplace_back(two);
	std::shared_ptr<HittableObject> world = std::make_shared<HittableList>(objectList, 2);

	for (int j = 0; j < windowHeight; j++)
	{
		for (int i = 0; i < windowWidth; i++)
		{
			float rayPosX = float(i) / float(windowWidth);
			float rayPosY =  float(j) / float(windowHeight);

			Ray r(origin, upperLeftCorner + (rayPosX * horizontal) + (rayPosY * vertical));

			glm::vec3 p = r.PointAtParameter(2.0f);
			glm::vec3 col = Colour(r, world);

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			glm::ivec2 pixelPosition = glm::vec2(i, j);
			glm::ivec3 pixelColour = glm::vec3(ir, ig, ib);

			MCG::DrawPixel(pixelPosition, pixelColour);
			if (i % windowWidth == 0)
			{
				//std::cout << ir << " " << ig << " " << ib << std::endl;
			}
		}

	}


	// Draws a single pixel at the specified coordinates in the specified colour!


	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
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
