#pragma once

class Alive
{
public:

	int m_MaxHealth = 0;
	int m_ActualHealth = 0;
	int m_Shield = 0;
	int m_MAXSHield = 0;

/// <summary>
/// Cette fonction retourne la variable m_ActualHealth
/// </summary>
/// <returns> Un entier </returns>
	int GetHealth();

/// <summary>
/// Cette fonction retourne la variable m_MaxHealth
/// </summary>
/// <returns> Un entier </returns>
	int GetMaxHealth();

/// <summary>
/// Cette fonction ajout un entier a m_ActualHealth
/// </summary>
/// <param name="value"></param>
/// <returns> nothing </returns>
	void AddHealth(int value);

/// <summary>
/// Cette fonction retire un entier a m_ActualHealth
/// </summary>
/// <param name="value"></param>
/// <returns> nothing </returns>
	void SubtractHealth(int value);

};
