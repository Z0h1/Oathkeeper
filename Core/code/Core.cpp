#include "Core.h"
#include "GraphicSystem.h"
#include "Log.h"
#include "DynamicLibrary.h"

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

		Log::Get()->DrawLine( "Core: Загрузка завершена!" );
	}

	Core::~Core()
	{
		for ( auto& itDynamicLibrary : mDynamicLibrarys )
		{
			UnLoadModule( itDynamicLibrary.first );
		}
		mDynamicLibrarys.clear();

		Log::Get()->DrawLine( "Core: Завершение работы!" );

		delete Log::Get();
	}

	// Dynamic Library
	typedef void (*START_DLL_MODULE)( void );
	typedef void (*STOP_DLL_MODULE)( void );

	bool Core::LoadModule( const string& cModule )
	{
		if ( mDynamicLibrarys.find(cModule) == mDynamicLibrarys.end() )
		{
			DynamicLibrary* pModule = new DynamicLibrary( cModule );

			if ( pModule->CheckWork() )
			{
				START_DLL_MODULE pFunc = (START_DLL_MODULE)pModule->GetAddress( "Start_DynamicLibrary" );
				pFunc();

				mDynamicLibrarys[cModule] = pModule;

				Log::Get()->DrawLine( "Core: Модуль " + cModule + " загружен" );

				return true;
			}
			else
			{
				Log::Get()->DrawLine( "Core: Модуль " + cModule + " не работает!", MT_ERROR );
			}
		}
		else
		{
			Log::Get()->DrawLine( "Core: Модуль " + cModule + " уже загружен", MT_WARNING );
		}

		return false;
	}

	bool Core::UnLoadModule( const string& cModule )
	{
		if ( mDynamicLibrarys.find( cModule ) != mDynamicLibrarys.end() )
		{
			STOP_DLL_MODULE pFunc = (STOP_DLL_MODULE)mDynamicLibrarys[cModule]->GetAddress( "Stop_DynamicLibrary" );
			pFunc();

			Log::Get()->DrawLine( "Core: Модуль " + cModule + " выгружен" );

			return true;
		}
		else
		{
			Log::Get()->DrawLine( "Core: Модуль " + cModule + " не загружен", MT_WARNING );
		}

		return false;
	}

	// GraphicSystem
	void Core::AddGraphicSystem(GraphicSystem* pSystem)
	{
		if (mGraphicSystems.find(pSystem->GetType()) == mGraphicSystems.end())
		{
			mGraphicSystems.insert(_GraphicSystems::value_type(pSystem->GetType(), pSystem));
		}
	}

	void Core::RemoveGraphicSystem(GraphicSystem* pSystem, bool destroy)
	{
		auto itSystem = mGraphicSystems.find(pSystem->GetType());

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
}