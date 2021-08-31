#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Gun
{
public:
	sf::Sprite gun_sprite, crossair;
	sf::Texture gun_texture, crossair_texture;
	sf::Sound fire_sound;
	sf::SoundBuffer fire_sound_buffer;
	int gun_rect_x = 0;
	bool firing = false;

	void Load_gun_resources(void);
	void set_gun_position(sf::Vector2i pos);
	void fire_animation(void);

};

