#include <iostream>
#include <conio.h> 

#include "Oathkeeper.h"

using namespace std;

namespace Oathkeeper
{
	class Client
	{
	public:
		Client()
		{
			mCore = new Core();
			mStoped = true;
		}

		~Client()
		{
			delete mCore;
		}

		bool Init(void)
		{
			return true;
		}

		bool Deinit(void)
		{
			return true;
		}

		void Loop(void)
		{
			while (mStoped)
			{
				mCore->Loop(false);
			}
		}

	private:
		Core*	mCore;
		bool	mStoped;
	};

	void Run()
	{
		Client* pClient = new Client();
		pClient->Init();
		pClient->Loop();

		pClient->Deinit();
	}
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Oathkeeper::Run();
}