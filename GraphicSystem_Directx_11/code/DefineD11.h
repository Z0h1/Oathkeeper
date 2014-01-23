#pragma once
#pragma warning (disable : 4005)

#include <d3dx11.h>

#include "Common.h"

namespace Oathkeeper
{
	#if defined ( GS_DIRECTX_11_EXPORT )
	#	define OKD11_EXPORT __declspec( dllexport )
	#else
	#	define OKD11_EXPORT __declspec( dllimport )
	#endif
}