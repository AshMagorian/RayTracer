#include <memory>
#include <mutex>

class HittableObject;
class Tracer;
class Camera;

class Application
{
public:

	Application() {}

	void Init();
	int Run();

	void SetScreenSize(int _option)
	{
		switch (_option)
		{
		case 1: m_windowHeight = 200; m_windowWidth = 400; break;
		case 2: m_windowHeight = 300; m_windowWidth = 600; break;
		case 3: m_windowHeight = 400; m_windowWidth = 800; break;
		case 4: m_windowHeight = 500; m_windowWidth = 1000; break;
		case 5: m_windowHeight = 600; m_windowWidth = 1200; break;
		}
	}
	void SetSamples(int _option) { m_numberOfSamples = _option; }
	void SetThreads(int _option) { m_numberOfThreads = _option; }
	void SetThreadMethod(int _option) { m_threadMethod = _option; }

	void BasicMultithreadingMethod();
	void ThreadPoolMethod();

	void DrawRow(int _currentPixel_y);
	void DrawBlock(int _blockNumber);
	void DrawPixel(int _currentPixel_x, int _currentPixel_y);

private:

	int m_windowWidth;
	int m_windowHeight;

	int m_numberOfSamples;

	int m_threadMethod;
	int m_numberOfThreads;
	int m_blockHeight;

	std::shared_ptr<HittableObject> m_world;
	std::shared_ptr<Tracer> m_tracer;
	std::shared_ptr<Camera> m_cam;

	std::mutex mtx;

	clock_t m_start;
	clock_t m_end;
	double time_elapsed;

	int m_pixelCount;
	float m_newPixelPercent;
	float m_oldPixelPercent;
};