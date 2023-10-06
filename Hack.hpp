#pragma once
#include <Windows.h>

class Hack
{
private:
	const uintptr_t baseAddress;
	const DWORD* healthModuleBase;
	const DWORD* bulletTimeModuleBase;

public:
	Hack() : baseAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("MaxPayne3.exe"))),
			 healthModuleBase(reinterpret_cast<DWORD*>(baseAddress + 0x015B2F80)),
		     bulletTimeModuleBase(reinterpret_cast<DWORD*>(baseAddress + 0x013B0EFC))
	{}

	 const uintptr_t GetBaseAddress() { return baseAddress; }
	 const DWORD* GetHealthModuleBases() { return healthModuleBase; }
	 const DWORD* GetBulletTimeModuleBase() { return bulletTimeModuleBase; }

	 void FreezeFloatValue(float* valuePointer, const float maximumValue)
	 {
		 float currentValue = *valuePointer;
		 if (currentValue < maximumValue)
		 {
			 *valuePointer = maximumValue;
		 }
	 }
};