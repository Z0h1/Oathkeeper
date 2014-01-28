#pragma once

#include "Define.h"

namespace Oathkeeper
{
	class OK_EXPORT Core
	{
	public:
		Core(const string& logName = L"Oathkeeper.html", const string& configFile = L"Oathkeeper.conf");
		~Core();

		void Loop(bool autoupdate);

		// Dynamic Library
		bool LoadModule( const string& cModule );
		bool UnLoadModule( const string& cModule );

		// Graphic System
		void AddGraphicSystem(GraphicSystem* pSystem);
		void RemoveGraphicSystem(GraphicSystem* pSystem);

		static Core* Get(void);
		static GraphicSystem* GetGraphicSystem(void);

	private:
		static Core* _SCore;

		// System
		static GraphicSystem*	_SGraphicSystem;

		typedef map< string, DynamicLibrary* >				_DynamicLibrarys;
		typedef map< _GraphicSystemType, GraphicSystem* >	_GraphicSystems;

		_DynamicLibrarys	mDynamicLibrarys;
		_GraphicSystems		mGraphicSystems;

		// std
		bool		mAutoupdate;
	};
}