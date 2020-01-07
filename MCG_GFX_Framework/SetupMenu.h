#pragma once
#include <memory>

class Application;

class SetupMenu
{
public:
	SetupMenu();

	void MainMenu(std::shared_ptr<Application> _app);

	void PrintMenu();
	int ValidOptionSelect(int _max);

	void ChangeScreenSize();
	void ChangeSamples();
	void ChangeThreads();
	void ChangeThreadMethod();
	void ChangeDepth();
	void ChangeScene();

private:
	int m_screenSizeOption;
	int m_sampleNumber;
	int m_numberOfThreads;
	int m_multithreadingMethod;
	int m_depth;
	int m_scene;
};