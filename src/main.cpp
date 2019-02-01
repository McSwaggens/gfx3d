#include <iostream>
#include "Engine.h"

class TestApp : public Application
{
private:
public:

	TestApp() = default;

	void Init()
	{
	}

	void Update()
	{
	}

	void Destroy()
	{
	}
};

int main(int argc, char* argv[])
{
	Application* app = new TestApp();
	g_engine->Start(app);
	return 0;
}

