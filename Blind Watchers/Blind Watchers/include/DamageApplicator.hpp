#pragma once

#include "Bullet.h"
#include "Pawn.h"

class damageApplicator : public npcCollisionObserver
{
public:
	damageApplicator(std::vector<std::shared_ptr<Pawn>>& t_pawns) : m_pawns(t_pawns)
	{
	}
	void listen(collisionInfo& t_bulletInfo)
	{
		for (unsigned int i = 0; i < m_pawns.size(); i++)
		{
			if (t_bulletInfo.collidedNPC.left == m_pawns.at(i)->getBounds().left && t_bulletInfo.collidedNPC.top == m_pawns.at(i)->getBounds().top)
			{
				m_pawns.at(i)->applyDamage(t_bulletInfo.collidingBullet.m_damage);
			}
		}
	}
private:
	std::vector< std::shared_ptr<Pawn> >& m_pawns;
};
