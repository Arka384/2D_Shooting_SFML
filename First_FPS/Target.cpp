#include "Target.hpp"

void Target::Load_target_resources(void)
{
	if (!target_texture.loadFromFile("Resources/Sprites/target.png"))
		exit(1);
	if (!target_hit_buffer.loadFromFile("Resources/Sounds/bullet-impact-metal.wav"))
		exit(1);
	if (!time_start_buffer.loadFromFile("Resources/Sounds/time_start.wav"))
		exit(1);
	if (!time_up_buffer.loadFromFile("Resources/Sounds/time_end.wav"))
		exit(1);
	target_sprite.setTexture(target_texture);
	target_hit.setBuffer(target_hit_buffer);
	target_hit.setVolume(50.f);
	time_start.setBuffer(time_start_buffer);
	time_start.setVolume(20.f);
	time_up.setBuffer(time_up_buffer);
}

void Target::Load_target_table(void)
{
	std::ifstream input("Resources/target_table.txt");
	if (!input.is_open())
		exit(1);

	int number = 0;
	taget_pos p;
	while (input >> number) {
		p.x = number;
		input >> number;
		p.y = number;
		input >> number;
		p.scale = (float)number / 100;
		target_table.push_back(p);
	}
	input.close();

	//for (int i = 0; i < target_table.size(); i++)
	//	std::cout << target_table[i].x << " " << target_table[i].y << " " << target_table[i].scale << std::endl;
}

void Target::spawn_target(void)
{
	int n = rand() % target_table.size();
	target_sprite.setScale(target_table[n].scale, target_table[n].scale);
	target_sprite.setPosition(target_table[n].x, target_table[n].y);
}
