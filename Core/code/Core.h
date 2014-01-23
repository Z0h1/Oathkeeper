#pragma once

#include "Define.h"

namespace Oathkeeper
{
	class OK_EXPORT Core
	{
	public:
		Core(const string& logName = "Oathkeeper.log", const string& configFile = "Oathkeeper.conf");
		~Core();

		// Graphic System
		void AddGraphicSystem(GraphicSystem* pSystem);
		void RemoveGraphicSystem(GraphicSystem* pSystem, bool destroy = true);

		static Core* Get(void);
		static GraphicSystem* GetGraphicSystem(void);

	private:
		static Core* _SCore;

		// System
		static GraphicSystem*	_SGraphicSystem;

		//typedef map< string, DynamicLibrary* >				_lDynamicLibrary;
		typedef map< _GraphicSystemType, GraphicSystem* >	_GraphicSystems;

		_GraphicSystems	mGraphicSystems;
	};
};