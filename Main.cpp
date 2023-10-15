#include <iostream>
#include <thread>
#include "Hack.hpp"

namespace Constants
{
    const float MAXIMUM_HEALTH = 300.0f;
    const float MAXIMUM_BULLET_TIME = 1.0f;

    const int MULLISECONDS_TO_SLEEP = 100;
}

DWORD __stdcall HackThread(const LPVOID parameter)
{
    Hack hack;

    const HMODULE* const ourModule = static_cast<HMODULE*>(parameter);

    while (!GetAsyncKeyState(VK_END))
    {
        hack.SetHealth(Constants::MAXIMUM_HEALTH);
        hack.SetBulletTime(Constants::MAXIMUM_BULLET_TIME);

        Sleep(Constants::MULLISECONDS_TO_SLEEP);
    }

    HMODULE instance = *ourModule;
    delete ourModule;
    FreeLibraryAndExitThread(instance, 0);

    return 0;
}

BOOL WINAPI DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(instance);

        HMODULE* const ourModule = new HMODULE;
        *ourModule = instance;

        const HANDLE thread = CreateThread(nullptr, 0, HackThread, ourModule, 0, nullptr);

        if (thread)
        {
            CloseHandle(thread);
        }
    }

    return TRUE;
}