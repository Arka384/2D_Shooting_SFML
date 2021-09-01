#include "Target.hpp"

void Target::Load_target_resources(void)
{
	if (!target_texture.loadFromFile("Resources/Sprites/target.png"))
		exit(1);
	target_sprite.setTexture(target_texture);
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
