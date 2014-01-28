#include "Core.h"
#include "GraphicSystem.h"
#include "Log.h"
#include "DynamicLibrary.h"
#include "ConfigFile.h"

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

		// Init Config
		ConfigFile* config = new ConfigFile(configFile);

		for (auto& it : config->Get())
		{
			if (it.first == L"load_module")
			{
				LoadModule(it.second);
			}
			else if (it.first == L"set_render_system")
			{
				if (it.second == L"DirectX_11" || it.second == L"directX_11" || it.second == L"Directx_11" || it.second == L"directx_11"
					|| it.second == L"DirectX 11" || it.second == L"directX 11" || it.second == L"Directx 11" || it.second == L"directx 11"
					|| it.second == L"DirectX11" || it.second == L"directX11" || it.second == L"Directx11" || it.second == L"directx11"
					|| it.second == L"11")
				{
					//ChangeRenderSystem( GT_DIRECTX_11 );
				}
				else if (it.second == L"DirectX_9" || it.second == L"directX_9" || it.second == L"Directx_9" || it.second == L"directx_9"
					|| it.second == L"DirectX 9" || it.second == L"directX 9" || it.second == L"Directx 9" || it.second == L"directx 9"
					|| it.second == L"DirectX9" || it.second == L"directX9" || it.second == L"Directx9" || it.second == L"directx9"
					|| it.second == L"9")
				{
					//ChangeRenderSystem( GT_DIRECTX_9 );
				}
			}
		}

		Log::Get()->DrawLine(L"Core: Загрузка завершена!");
	}

	Core::~Core()
	{
		for ( auto itDynamicLibrary : mDynamicLibrarys )
		{
			UnLoadModule( itDynamicLibrary.first );
		}
		mDynamicLibrarys.clear();

		Log::Get()->DrawLine(L"Core: Завершение работы!");

		delete Log::Get();
	}

	void Core::Loop(bool autoupdate)
	{
		mAutoupdate = autoupdate;

		while (mAutoupdate)
		{

			// error mAutoupdate = false;
		}
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
				START_DLL_MODULE pFunc = (START_DLL_MODULE)pModule->GetAddress("Start_DynamicLibrary");
				pFunc();

				mDynamicLibrarys[cModule] = pModule;

				Log::Get()->DrawLine(L"Core: Модуль " + cModule + L" загружен");

				return true;
			}
			else
			{
				Log::Get()->DrawLine(L"Core: Модуль " + cModule + L" не работает!", MT_ERROR);
			}
		}
		else
		{
			Log::Get()->DrawLine(L"Core: Модуль " + cModule + L" уже загружен", MT_WARNING);
		}

		return false;
	}

	bool Core::UnLoadModule( const string& cModule )
	{
		if ( mDynamicLibrarys.find( cModule ) != mDynamicLibrarys.end() )
		{
			STOP_DLL_MODULE pFunc = (STOP_DLL_MODULE)mDynamicLibrarys[cModule]->GetAddress("Stop_DynamicLibrary");
			pFunc();

			Log::Get()->DrawLine(L"Core: Модуль " + cModule + L" выгружен");

			return true;
		}
		else
		{
			Log::Get()->DrawLine(L"Core: Модуль " + cModule + L" не загружен", MT_WARNING);
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

	void Core::RemoveGraphicSystem(GraphicSystem* pSystem)
	{
		auto itSystem = mGraphicSystems.find(pSystem->GetType());

		if (itSystem != mGraphicSystems.end())
		{
			if (_SGraphicSystem == pSystem)
				_SGraphicSystem = nullptr;

			mGraphicSystems.erase(itSystem);
		}
	}
}