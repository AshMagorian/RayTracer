#include "SetupMenu.h"

#include "Application.h"
#include <thread>
#include <iostream>

SetupMenu::SetupMenu()
{
	m_sampleNumber = 50;
	m_screenSizeOption = 2;
	m_numberOfThreads = std::thread::hardware_concurrency();
	m_multithreadingMethod = 1;
}

void SetupMenu::MainMenu(std::shared_ptr<Application> _app)
{
	bool exitflag = false;

	do 
	{
		PrintMenu();
		int option = ValidOptionSelect(5);

		switch (option)
		{
		case 1: ChangeScreenSize(); break;
		case 2: ChangeSamples(); break;
		case 3: ChangeThreads(); break;
		case 4: ChangeThreadMethod(); break;
		case 5: exitflag = true; break;
		default: break; 
		}

	} while (exitflag == false);

	_app->SetScreenSize(m_screenSizeOption);
	_app->SetSamples(m_sampleNumber);
	_app->SetThreads(m_numberOfThreads);
	_app->SetThreadMethod(m_multithreadingMethod);
}

void SetupMenu::PrintMenu()
{
	system("CLS");
	std::cout <<
		"===============\n"
		"RAY TRACER SETUP\n"
		"===============\n\n"
		"[1] Screen Size   (Currently selected: ";
	switch (m_screenSizeOption)
	{
	case 1: std::cout << "200x400)\n"; break;
	case 2: std::cout << "300x600)\n"; break;
	case 3: std::cout << "400x800)\n"; break;
	case 4: std::cout << "500x1000)\n"; break;
	case 5: std::cout << "600x1200)\n"; break;
	default: break;
	}
	std::cout <<
		"[2] Number of Samples   (Currently selected: " << m_sampleNumber << ")\n"
		"[3] Number of threads   (Currently selected: " << m_numberOfThreads << ")\n"
		"[4] Multithreading method    (Currently selected: ";
	switch (m_multithreadingMethod)
	{
	case 1: std::cout << "Threads divided to screen blocks) \n\n"; break;
	case 2: std::cout << "Threadpool method) \n\n"; break;
	default: break;
	}
	std::cout << "[5] Start Rendering\n\n"
		"Select your option:\n\n";
}

int SetupMenu::ValidOptionSelect(int _max)
{
	int option = 0;
	char buff[20] = { 0 };
	std::cin >> buff;
	option = buff[0] - 48;
	while (option < 1 || option > _max)
	{
		std::cout << "\nInvalid input! Try again!\n";
		std::cin >> buff;
		option = buff[0] - 48;
	}
	return option;
}

void SetupMenu::ChangeScreenSize()
{
	system("CLS");
	std::cout << "[1] 200x400\n"
		"[2] 300x600\n"
		"[3] 400x800\n"
		"[4] 500x1000\n"
		"[5] 600x1200\n\n"
		"Select your option: \n\n";

	int option = ValidOptionSelect(5);
	m_screenSizeOption = option;
}

void SetupMenu::ChangeSamples()
{
	system("CLS");
	std::cout << "Enter the amount of samples you would like to use per pixel (max 500):\n\n";

	int option = 0;

	std::cin >> option;

	while (option < 1 || option > 500)
	{
		std::cout << "\nInvalid input! Try again!\n";
		std::cin >> option;
	}

	m_sampleNumber = option;
}

void SetupMenu::ChangeThreads()
{
	system("CLS");
	std::cout << "Enter the amount of threads you would like to use (max " << std::thread::hardware_concurrency() <<"):\n\n";

	int option = 0;

	std::cin >> option;

	while (option < 1 || option > std::thread::hardware_concurrency())
	{
		std::cout << "\nInvalid input! Try again!\n";
		std::cin >> option;
	}
	m_numberOfThreads = option;
}

void SetupMenu::ChangeThreadMethod()
{
	system("CLS");
	std::cout << "[1] Screen is divided into blocks with a thread assigned to render each block\n"
		"[2] Threadpool method\n";

	int option = ValidOptionSelect(2);
	m_multithreadingMethod = option;
}