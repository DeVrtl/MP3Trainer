#include <iostream>
#include <thread>
#include "Hack.hpp"

namespace Offsets 
{
	constexpr std::ptrdiff_t health = 0x358;
	constexpr std::ptrdiff_t bulletTime = 0xC;
}

namespace Constants 
{
	const float MAXIMUM_HEALTH = 300.0f;
	const float MAXIMUM_BULLET_TIME = 1.0f;
}

void HackThread(const HMODULE instance)
{
	Hack hack;

	while (!GetAsyncKeyState(VK_END))
	{
		float* healthPointer = reinterpret_cast<float*>(*hack.GetHealthModuleBases() + Offsets::health);;
		float* bulletTimePointer = reinterpret_cast<float*>(*hack.GetBulletTimeModuleBase() + Offsets::bulletTime);;

		hack.FreezeFloatValue(healthPointer, Constants::MAXIMUM_HEALTH);
		hack.FreezeFloatValue(bulletTimePointer, Constants::MAXIMUM_BULLET_TIME);

		Sleep(100);
	}

	FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), instance, 0, nullptr);

		if (thread)
		{
			CloseHandle(thread);
		}
	}
	
	return TRUE;
}