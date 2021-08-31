#pragma once
#include <SFML/Graphics.hpp>

class Target
{
public:
	sf::Sprite target_sprite;
	sf::Texture target_texture;
	float spawn_time = 0.5;

	void Load_target_resources(void);
	void spawn_target(void);
};

