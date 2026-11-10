#pragma once


#ifdef AG_PLATFORM_WINDOWS
	#ifdef AG_BUILD_DLL
		#define AEGIS_API __declspec(dllexport)
	#else
		#define AEGIS_API __declspec(dllimport)
	#endif
#else
#error Aegis only supports Windows!
#endif
