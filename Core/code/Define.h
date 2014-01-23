#pragma once
#pragma warning (disable : 4251)

#include <string>
#include <sstream>

#include <io.h>
#include <iostream>
#include <fstream>

#include <assert.h>

#include <vector>
#include <list>
#include <map>

using namespace std;

namespace Oathkeeper
{
	#if defined ( CORE_EXPORT )
	#	define OK_EXPORT __declspec( dllexport )
	#else
	#	define OK_EXPORT __declspec( dllimport )
	#endif

	enum _MessageType
	{
		MT_NORMAL,
		MT_WARNING,
		MT_ERROR,
		MT_NONE
	};

	enum _GraphicSystemType
	{
		GT_DIRECTX_11,
		GT_NONE
	};

	class Core;
	class GraphicSystem;
	class Log;
}