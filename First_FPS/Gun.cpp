#include "Gun.hpp"

void Gun::Load_gun_resources(void)
{

	if (!gun_texture.loadFromFile("Resources/Sprites/UZI.png")) exit(1);
	//if (!gun_texture.loadFromFile("Resources/Sprites/M4.png")) exit(1);
	if (!crossair_texture.loadFromFile("Resources/Sprites/crossair.png")) exit(1);
	if (!fire_sound_buffer.loadFromFile("Resources/Sounds/Uzi_Single_Shot_trim.wav")) exit(1);
	
	gun_sprite.setTexture(gun_texture);
	gun_sprite.setTextureRect(sf::IntRect(0, 0, 160, 175));

	crossair.setTexture(crossair_texture);
	crossair.setOrigin(crossair.getGlobalBounds().width / 2, crossair.getGlobalBounds().height / 2);
	fire_sound.setBuffer(fire_sound_buffer);
}

void Gun::set_gun_position(sf::Vector2i pos)
{
	crossair.setPosition(pos.x, pos.y);
	if (pos.x <= 683) {
		gun_sprite.setPosition(pos.x + 100, pos.y - 5);
		gun_sprite.setScale(1, 1);
	}
	else {
		gun_sprite.setPosition(pos.x - 100, pos.y - 5);
		gun_sprite.setScale(-1, 1);
	}
}

void Gun::fire_animation(void)
{

	gun_rect_x += 160;
	if (gun_rect_x == (160 * 3))
		gun_rect_x = 0;
	
	gun_sprite.setTextureRect(sf::IntRect(gun_rect_x, 0, 160, 175));

	/*
	if (gun_rect_x == 0) {
		gun_rect_x = 160;
		gun_sprite.setTextureRect(sf::IntRect(gun_rect_x, 0, 175, 140));
	}
	else if (gun_rect_x == 160) {
		gun_rect_x = 336;
		gun_sprite.setTextureRect(sf::IntRect(gun_rect_x, 0, 186, 140));
	}
	else
	{
		gun_rect_x = 0;
		gun_sprite.setTextureRect(sf::IntRect(gun_rect_x, 0, 160, 140));
	}
	*/
}
