#include "ShieldClass.h"
#include <iostream>
#include "../ManagerGroup/GameManager.h"

ShieldClass::ShieldClass(int Value, int regenSpeed)
{
	m_ShieldregenSpeed = regenSpeed;
	m_ShieldValue = Value;
	Shield = true;
}

void ShieldClass::Use(int linkModule)
{
	if (Clock.getElapsedTime().asMilliseconds() > 500)
	{

		Clock.restart();

		if (GameManager::GetInstance()->m_PlayerInstance->m_Shield < GameManager::GetInstance()->m_PlayerInstance->m_MAXSHield)
		{
			GameManager::GetInstance()->m_PlayerInstance->m_Shield++;
		}
	}
}
