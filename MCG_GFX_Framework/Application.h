#include <memory>

class HittableObject;
class Tracer;
class Camera;

class Application
{
public:

	Application() {}

	void Init();
	int Run();

	void DrawRow();

private:

	int m_windowWidth;
	int m_windowHeight;

	int m_currentPixel_x;
	int m_currentPixel_y;

	int m_numberOfSamples;

	std::shared_ptr<HittableObject> m_world;
	std::shared_ptr<Tracer> m_tracer;
	std::shared_ptr<Camera> m_cam;




	int m_pixelCount;
	float m_newPixelPercent;
	float m_oldPixelPercent;
};