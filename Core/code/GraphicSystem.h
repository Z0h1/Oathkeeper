#pragma once

#include "Common.h"

namespace Oathkeeper
{
	class OK_EXPORT GraphicSystem
	{
	public:
		GraphicSystem();
		~GraphicSystem();

		const _GraphicSystemType GetType(void) const { return mType; }

	private:
		_GraphicSystemType	mType;
	};
};