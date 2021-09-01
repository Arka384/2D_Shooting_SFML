#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <fstream>

class Target
{
public:
	sf::Sprite target_sprite;
	sf::Texture target_texture;
	sf::SoundBuffer target_hit_buffer,time_start_buffer, time_up_buffer;
	sf::Sound target_hit, time_start, time_up;
	float spawn_time = 0.5;

	typedef struct taget_pos {
		float scale;
		int x, y;
	}taget_pos;
	std::vector<taget_pos> target_table;

	void Load_target_resources(void);
	void Load_target_table(void);
	void spawn_target(void);
};

