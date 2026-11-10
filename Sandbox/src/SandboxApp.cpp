#include <Aegis.h>

class Sandbox : public Aegis::Application
{
public:
	Sandbox()
	{
	}
	~Sandbox()
	{
	}
};

Aegis::Application* Aegis::CreateApplication()
{
	return new Sandbox();
}