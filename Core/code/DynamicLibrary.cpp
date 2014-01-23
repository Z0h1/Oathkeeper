#include "DynamicLibrary.h"

namespace Oathkeeper
{
	DynamicLibrary::DynamicLibrary( const string& cFileName )
	{
		m_bWork = true;
		m_cFileName = cFileName;

		if ( cFileName.substr( cFileName.length() - 4, 4 ) != ".dll" )
		{
			m_cFileName += ".dll";
		}

		m_phDll = LoadLibraryEx( m_cFileName.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH );

		if ( !m_phDll )
		{
			LPVOID ErrorBuffer; 
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR) &ErrorBuffer, 0, NULL );

			string error = (char*)ErrorBuffer;
			LocalFree( ErrorBuffer );

			Log::Get()->DrawLine( "DynamicLibrary: " + error, MT_ERROR );
			m_bWork = false;
		}
	}

	DynamicLibrary::~DynamicLibrary( void )
	{
		if ( !FreeLibrary( m_phDll ) )
		{
			Log::Get()->DrawLine( "DynamicLibrary: Невозможно выгрузить модуль", MT_ERROR );
		}
	}

	void* DynamicLibrary::GetAddress( const string& cFunctionName )
	{
		return GetProcAddress( m_phDll, cFunctionName.c_str() );
	}
}