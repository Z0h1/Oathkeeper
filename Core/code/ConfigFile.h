#pragma once

#include "Common.h"

namespace Oathkeeper
{
	typedef vector< pair<string, string> >	_Configs;

	class OK_EXPORT ConfigFile
	{
	public:
		ConfigFile(const string& configfile);
		~ConfigFile();

		const _Configs& Get(void) { return mConfigs; };

	private:
		wifstream	mFile;
		_Configs	mConfigs;
	};
}