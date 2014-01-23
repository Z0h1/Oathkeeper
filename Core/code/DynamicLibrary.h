#pragma once

#include "Common.h"

namespace Oathkeeper
{
	class OK_EXPORT DynamicLibrary
	{
	public:
		DynamicLibrary( const string& cFileName );
		~DynamicLibrary( void );

		void* GetAddress( const string& cFunctionName );
		bool CheckWork( void ) const { return m_bWork; }

	private:
		HINSTANCE		m_phDll;
		bool			m_bWork;
		string			m_cFileName;
	};
}