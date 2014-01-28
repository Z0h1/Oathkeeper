#include "Log.h"

namespace Oathkeeper
{
	Log* Log::_SLog = nullptr;

	Log* Log::Get(void)
	{
		return _SLog;
	}

	Log::Log(const string& logName)
	{
		_SLog = this;

		mLog.open( logName.c_str() );
		mLog.imbue(std::locale(""));

		mLog << L"<html>" << endl;
		mLog << L"<head>" << endl;
		mLog << L"<title>Work log</title>" << endl;
		mLog << L"<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << endl;
		mLog << L"</head>" << endl;
		mLog << L"<body>" << endl;
		mLog << L"<div class=\"header\"><b>Hailstorm Engine - Work log</b></div>" << endl;
		
		wcout.imbue(std::locale(""));
	}

	Log::~Log()
	{
		mLog << L"</body>" << endl;
		mLog << L"</html>" << endl;

		mLog.close();
	}

	void Log::DrawLine(const string& text, _MessageType type)
	{
		if (mLog)
		{
			string warning;

			if (type == MT_NORMAL)
			{
				warning = L"normal";
			}
			else if (type == MT_WARNING)
			{
				warning = L"warning";
			}
			else if (type == MT_ERROR)
			{
				warning = L"error";
			}

			mLog << L"<div class=" + warning + L">" + text + L"</div>" << endl;

			wcout << warning << L": " << text << endl;

			mLog.flush();
		}
	}
}