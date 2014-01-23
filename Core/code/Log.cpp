#include "Log.h"

namespace Oathkeeper
{
	Log* Log::_SLog = nullptr;

	Log::Log(const string& logName)
	{
		_SLog = this;

		mLog.open( logName.c_str() );

		mLog << "<html>" << endl;
		mLog << "<head>" << endl;
		mLog << "<title>Work log</title>" << endl;
		mLog << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << endl;
		mLog << "</head>" << endl;
		mLog << "<body>" << endl;
		mLog << "<div class=\"header\"><b>Hailstorm Engine - Work log</b></div>" << endl;
	}

	Log::~Log()
	{
		mLog << "</body>" << endl;
		mLog << "</html>" << endl;

		mLog.close();
	}

	void Log::DrawLine(const string& text, _MessageType type)
	{
		if (mLog)
		{
			string warning;

			if (type == MT_NORMAL)
			{
				warning = "normal";
			}
			else if (type == MT_WARNING)
			{
				warning = "warning";
			}
			else if (type == MT_ERROR)
			{
				warning = "error";
			}

			mLog << "<div class=" + warning + ">" + text + "</div>" << endl;

			mLog.flush();
		}
	}
}