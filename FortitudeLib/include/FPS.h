#include <vector>

class FPS
{
private:
	std::vector<float> fps;
	std::vector<float> framedelta;

	float avg;
	int index;
public:
	FPS();
	void init();
	void log(float frametime);
	int get();
};