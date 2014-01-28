#include "StringConverter.h"

namespace Oathkeeper
{
	void Trim( string& str, bool left, bool right )
	{
		const string delims = L" \t\r";

        if ( right )
		{
            str.erase( str.find_last_not_of( delims ) + 1 ); // trim right
		}

        if ( left )
		{
            str.erase( 0, str.find_first_not_of( delims ) ); // trim left
		}
	}

	string ToString(const wchar_t* value)
	{
		wstringstream buffer;
		buffer << value;
		return buffer.str();
	}
}