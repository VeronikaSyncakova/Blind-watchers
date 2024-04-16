#include "Pawn.h"

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}

void Pawn::applyDamage(int t_damageAmt)
{
	m_health -= t_damageAmt;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	else if (m_health <= 0.f)
	{
		expire();
	}
}

