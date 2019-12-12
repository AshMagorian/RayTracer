#include "Application.h"



int main( int argc, char *argv[] )
{
	std::shared_ptr<Application> app = std::make_shared<Application>();

	app->Init();

	return app->Run();
}

