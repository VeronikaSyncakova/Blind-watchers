#ifndef PARTICLE_SPAWNER_HPP
#define PARTICLE_SPAWNER_HPP

#include "Particles.h"
#include "simpleMaths.h"


class ParticleSpawner
{
public:
	/// <summary>
	/// Pass in a spawn position and a displacement to spawn a smear of "blood"
	///  create an explosive blood splatter 
	/// </summary>
	static void spawnBlood(sf::Vector2f t_displacement, sf::Vector2f t_spawnPos)
	{
		int amt = rand() % 30 + 3;
		for (int j = 0; j < amt; j++)
		{
			sf::Vector2f direction = sf::Vector2f(rand() / float(RAND_MAX), rand() / float(RAND_MAX));

			float x = 0.1f;

			if (t_displacement.x > 0.1f)
			{
				direction.x = rand() / float(RAND_MAX);
			}
			else if (t_displacement.x < 0.1f)
			{
				direction.x = -(rand() / float(RAND_MAX));
			}
			else
			{
				direction.x = rand() / float(RAND_MAX);
			}
			if (t_displacement.y > 0.1f)
			{
				direction.y = rand() / float(RAND_MAX);
			}
			else if (t_displacement.y < 0.1f)
			{
				direction.y = -(rand() / float(RAND_MAX));
			}
			else
			{
				direction.y = rand() / float(RAND_MAX);
			}
			x = rand() / float(RAND_MAX) / 10.f * 3.f - 0.15f;
			direction.y += x;
			x = rand() / float(RAND_MAX) / 10.f * 3.f - 0.15f;
			direction.x += x;


			sf::Color color;

			color = sf::Color(0, (rand() % 80) + 175, 0, 255);

			ParticleSystem::getInstance().spawnNewParticle(4.f, t_spawnPos, direction, 1000.f, 0.5f, color);
		}
	}

	static void explode(sf::Vector2f t_position)
	{
		int amt = rand() % 100;
		for (int j = 0; j < amt; j++)
		{
			sf::Vector2f direction;
			direction.x = (rand() / float(RAND_MAX) * 3.f) - 1.f;
			direction.y = (rand() / float(RAND_MAX) * 3.f) - 1.f;
			sf::Color col;
			col.r = rand() % 255;
			col.g = rand() % 255;
			col.b = rand() % 255;
			col.a = 255;

			ParticleSystem::getInstance().spawnNewParticle(2.f, t_position, direction, 300.f, 0.5f, col);
		}
	}
};

#endif // !PARTICLE_SPAWNER_HPP
