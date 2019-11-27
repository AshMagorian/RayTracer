
#include <cmath>
#include <iostream>

#include "MCG_GFX_Lib.h"
#include "Ray.h"

bool HitSphere(glm::vec3 &center, float radius, Ray& r)
{
	glm::vec3 oc = r.GetOrigin() - center; // A - C
	float a = glm::dot(r.GetDirection(), r.GetDirection()); // finding the a, b and c values for b*b - 4ac equation (the discriminant of the quadratic equation)
	float b = 2.0f * glm::dot(oc, r.GetDirection());
	float c = glm::dot(oc, oc) - (radius * radius);
	float discriminant = (b * b) - (4.0f *a*c);

	return (discriminant > 0);
}

glm::vec3 Colour(Ray& r)
{
	if (HitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r))
	{
		return glm::vec3(1.0f, 0.0f, 0.0f);
	}

	glm::vec3 unitDirection = glm::normalize(r.GetDirection()); // normalizes the ray direction
	float t = 0.5f* (unitDirection.y + 1.0f); // scales t between 0 and 1

	return ((1.0f - t) *glm::vec3(1.0f, 1.0f, 1.0f)) + (t * glm::vec3(0.5f, 0.7f, 1.0f));
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


	for (int j = 0; j < windowHeight; j++)
	{
		for (int i = 0; i < windowWidth; i++)
		{
			float rayPosX = float(i) / float(windowWidth);
			float rayPosY =  float(j) / float(windowHeight);

			Ray r(origin, upperLeftCorner + (rayPosX * horizontal) + (rayPosY * vertical));
			glm::vec3 col = Colour(r);

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
