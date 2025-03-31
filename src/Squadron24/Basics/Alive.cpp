#include "Alive.h"

int Alive::GetHealth()
{
	return this->m_ActualHealth;
}

int Alive::GetMaxHealth()
{
	return this->m_MaxHealth;
}

void Alive::AddHealth(int value)
{
	if (this->m_ActualHealth += value > this->m_MaxHealth)
	{
		this->m_ActualHealth = this->m_MaxHealth;
	}
}

void Alive::SubtractHealth(int value)
{
	this->m_ActualHealth -= value;
	if (m_ActualHealth <= 0)
	{
		this->m_ActualHealth = 0;
	}
}
