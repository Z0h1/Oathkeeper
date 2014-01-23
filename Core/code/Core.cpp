#include "Core.h"
#include "GraphicSystem.h"
#include "Log.h"

namespace Oathkeeper
{
	Core* Core::_SCore = nullptr;
	GraphicSystem* Core::_SGraphicSystem = nullptr;

	Core* Core::Get(void)
	{
		assert( _SCore );
		return _SCore;
	}

	GraphicSystem* Core::GetGraphicSystem(void)
	{
		assert( _SGraphicSystem );
		return _SGraphicSystem;
	}

	Core::Core(const string& logName, const string& configFile)
	{
		_SCore = this;

		// Init log
		Log* log = Log::Get();
		log = new Log(logName);

		Log::Get()->DrawLine("Hello world");
	}

	Core::~Core()
	{
	}

	void Core::AddGraphicSystem(GraphicSystem* pSystem)
	{
		if (mGraphicSystems.find(pSystem->GetType()) == mGraphicSystems.end())
		{
			mGraphicSystems.insert(_GraphicSystems::value_type(pSystem->GetType(), pSystem));
		}
	}

	void Core::RemoveGraphicSystem(GraphicSystem* pSystem, bool destroy)
	{
		_GraphicSystems::iterator itSystem = mGraphicSystems.find(pSystem->GetType());

		if (itSystem != mGraphicSystems.end())
		{
			if (_SGraphicSystem == pSystem)
			{
				_SGraphicSystem = nullptr;
			}

			mGraphicSystems.erase(itSystem);

			if (destroy)
			{
				delete pSystem;
			}
		}
	}
};