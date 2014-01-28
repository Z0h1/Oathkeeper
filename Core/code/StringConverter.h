#pragma once

#include "Define.h"

namespace Oathkeeper
{
	void OK_EXPORT Trim( string& str, bool left = true, bool right = true );
	string OK_EXPORT ToString(const wchar_t* value);
}