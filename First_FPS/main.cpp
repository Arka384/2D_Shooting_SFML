#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gun.hpp"
#include "Target.hpp"

bool hit_target(sf::Vector2i pos, Target t);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test", sf::Style::Close);
	sf::Vector2i mousePos;
	Gun uzi;
	Target target;
	uzi.Load_gun_resources();
	target.Load_target_resources();
	target.spawn_target();

	window.setMouseCursorVisible(false);
	sf::Clock clk;
	sf::Time t;
	float dt = 0, timer = 0.2;

	while (window.isOpen()) {
		t = clk.restart();
		dt = t.asSeconds();
		

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					window.close();
			case sf::Event::MouseButtonPressed:
				uzi.firing = true;
				break;
			case sf::Event::MouseButtonReleased:
				uzi.firing = false;
				break;
			default:
				break;
			}
		}

		mousePos = sf::Mouse::getPosition(window);
		uzi.set_gun_position(mousePos);
		if (uzi.firing) {
			if (uzi.fire_sound.getStatus() != sf::Sound::Status::Playing)
				uzi.fire_sound.play();
			uzi.fire_animation();
			if (hit_target(mousePos, target)) {
				timer -= dt;
				if (timer <= 0) {
					target.spawn_target();
					timer = 0.2;
				}
				
			}
				
		}
		else
			uzi.gun_sprite.setTextureRect(sf::IntRect(0, 0, 160, 175));

		window.clear();

		window.draw(target.target_sprite);
		window.draw(uzi.gun_sprite);
		window.draw(uzi.crossair);
		window.display();
	}
}

bool hit_target(sf::Vector2i pos, Target t)
{
	return pos.x > t.target_sprite.getPosition().x && pos.x < t.target_sprite.getPosition().x + t.target_sprite.getGlobalBounds().width
		&& pos.y > t.target_sprite.getPosition().y && pos.y < t.target_sprite.getPosition().y + t.target_sprite.getGlobalBounds().height;
}

