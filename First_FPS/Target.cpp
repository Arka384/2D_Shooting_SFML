#include "Target.hpp"

void Target::Load_target_resources(void)
{
	if (!target_texture.loadFromFile("Resources/Sprites/target.png"))
		exit(1);

	target_sprite.setTexture(target_texture);
	target_sprite.setScale(0.4, 0.4);
}

void Target::spawn_target(void)
{
	sf::Vector2i pos; 
	pos.x = rand() % static_cast<int>(1280 - target_sprite.getGlobalBounds().width);
	pos.y = rand() % static_cast<int>(720 - target_sprite.getGlobalBounds().height);

	target_sprite.setPosition(pos.x, pos.y);
}
