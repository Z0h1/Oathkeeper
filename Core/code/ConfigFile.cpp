#include "ConfigFile.h"

namespace Oathkeeper
{
	ConfigFile::ConfigFile(const string& configfile)
	{
		mFile.open(configfile.c_str(), ios::in);

		if (mFile)
		{
			wchar_t lineBuffer[256];
			string line, parametor, value;

			while (!mFile.eof())
			{
				mFile.getline(lineBuffer, 256);
				line = ToString(lineBuffer);

				// Пропуск пустых и "#" закоментированых строк
				if ( line.length() > 0 && line.at( 0 ) != '#' )
				{
					string::size_type separator_pos = line.find_first_of( L"=", 0 );
					if ( separator_pos != string::npos )
					{
						// parametor
						parametor = line.substr( 0, separator_pos );

						// value
						value = line.substr( separator_pos + 1, line.length() );

						// trim
						Trim( parametor );
						Trim( value );

						mConfigs.push_back(make_pair( parametor, value ));
					}
				}
			}
		}
		else
		{
			Log::Get()->DrawLine(L"ConfigFile: Файл \"" + configfile + L"\" не найден!", MT_ERROR);
		}
	}
}