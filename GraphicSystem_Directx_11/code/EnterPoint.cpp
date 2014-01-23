#include "DefineD11.h"
#include "GraphicSystemD11.h"

namespace Oathkeeper
{
	extern "C"
	{
		void OKD11_EXPORT Start_DynamicLibrary( void )
		{
			GraphicSystemD11* pSystem = new GraphicSystemD11();

			Core::Get()->AddGraphicSystem( pSystem );
		}

		void OKD11_EXPORT Stop_DynamicLibrary( void )
		{
			//GraphicSystemD11* pSystem = Core::GetCore()->GetRenderSystem( RST_DIRECTX_11 );

			//delete pSystem;
		}
	}
}