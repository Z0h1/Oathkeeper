#pragma once

#include "Define.h"

namespace Oathkeeper
{
	class OK_EXPORT Log
	{
	public:
		Log(const string& logName);
		~Log();

		void DrawLine(const string& text, _MessageType type = MT_NORMAL);

		static Log* Get(void);

	private:
		static Log*	_SLog;

		wofstream	mLog;
	};
}