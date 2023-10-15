#pragma once

#include <Windows.h>

namespace Offsets
{
	constexpr std::ptrdiff_t health = 0x358;
	constexpr std::ptrdiff_t bulletTime = 0xC;
	constexpr std::ptrdiff_t healthModuleOffset = 0x015B2F80;
	constexpr std::ptrdiff_t bulletTimeModuleOffset = 0x013B0EFC;
}

class MaxPayneModule final
{
private:
	const uintptr_t baseAddres;

public:
	
	MaxPayneModule() : baseAddres(reinterpret_cast<uintptr_t>(GetModuleHandle("MaxPayne3.exe")))
	{}

	const DWORD* GetSubModule(const std::ptrdiff_t offset) const
	{
		return reinterpret_cast<DWORD*>(baseAddres + offset);
	}
};

class Hack
{
private:
	const MaxPayneModule _maxPayne;

	const DWORD* _healthModuleBase;
	const DWORD* _bulletTimeModuleBase;

	float* _healthPointer;
	float* _bulletTimePointer;

	void FreezeFloatValue(float* valuePointer, const float maximumValue)
	{
		if (valuePointer == nullptr) 
		{
			return;
		}

		float currentValue = *valuePointer;
		if (currentValue < maximumValue)
		{
			*valuePointer = maximumValue;
		}
	}

public:
	Hack()  
	{
		_healthModuleBase = _maxPayne.GetSubModule(Offsets::healthModuleOffset);
		_bulletTimeModuleBase = _maxPayne.GetSubModule(Offsets::bulletTimeModuleOffset);
		_healthPointer = reinterpret_cast<float*>(*_healthModuleBase + Offsets::health);
		_bulletTimePointer = reinterpret_cast<float*>(*_bulletTimeModuleBase + Offsets::bulletTime);
	}

	 void SetHealth(float value)
	 {
		 FreezeFloatValue(_healthPointer, value);
	 }

	 void SetBulletTime(float value)
	 {
		 FreezeFloatValue(_bulletTimePointer, value);
	 }
};