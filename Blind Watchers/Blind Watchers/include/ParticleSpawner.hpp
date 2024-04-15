#ifndef PARTICLE_SPAWNER_HPP
#define PARTICLE_SPAWNER_HPP

#include "Particles.h"
#include "simpleMaths.h"

/// <summary>
/// Pass in a spawn position and a displacement to spawn a smear of "blood"
/// </summary>
class ParticleSpawner
{
public:
	static void spawnBlood(sf::Vector2f t_displacement, sf::Vector2f t_spawnPos)
	{
		int amt = rand() % 30 + 3;
		for (int j = 0; j < amt; j++)
		{
			sf::Vector2f direction = sf::Vector2f(rand() / RAND_MAX, rand() / RAND_MAX);

			float x = 0.1f;

			if (t_displacement.x > 0.1f)
			{
				direction.x = rand() / double(RAND_MAX);
			}
			else if (t_displacement.x < 0.1f)
			{
				direction.x = -(rand() / double(RAND_MAX));
			}
			else
			{
				direction.x = rand() / double(RAND_MAX);
			}
			if (t_displacement.y > 0.1f)
			{
				direction.y = rand() / double(RAND_MAX);
			}
			else if (t_displacement.y < 0.1f)
			{
				direction.y = -(rand() / double(RAND_MAX));
			}
			else
			{
				direction.y = rand() / double(RAND_MAX);
			}
			x = rand() / double(RAND_MAX) / 10.f * 3.f - 0.15f;
			direction.y += x;
			x = rand() / double(RAND_MAX) / 10.f * 3.f - 0.15f;
			direction.x += x;


			sf::Color color;

			color = sf::Color(0, (rand() % 80) + 175, 0, 255);

			ParticleSystem::getInstance().spawnNewParticle(2.f, t_spawnPos, direction, 1000.f, 0.5f, color);
		}
	}
};

#endif // !PARTICLE_SPAWNER_HPP
