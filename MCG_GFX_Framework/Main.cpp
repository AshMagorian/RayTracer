#include "Application.h"
#include "SetupMenu.h"


int main( int argc, char *argv[] )
{
	std::shared_ptr<Application> app = std::make_shared<Application>();

	std::shared_ptr<SetupMenu> setup = std::make_shared<SetupMenu>();
	setup->MainMenu(app);

	app->Init();

	return app->Run();
}

