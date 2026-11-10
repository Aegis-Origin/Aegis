#pragma once
#include "Core.h"
namespace Aegis {

	class AEGIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


