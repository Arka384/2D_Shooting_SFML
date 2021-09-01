#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Gun.hpp"
#include "Target.hpp"

bool hit_target(sf::Vector2i pos, Target t);

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1366, 680), "Test", sf::Style::Close);
	sf::Vector2i mousePos;
	Gun uzi;
	Target target;
	uzi.Load_gun_resources();
	target.Load_target_resources();
	target.Load_target_table();
	target.spawn_target();

	int Score = 0;
	sf::Text score_text, timer_text[2], ui_text[2];
	sf::Font font, ui_font;
	font.loadFromFile("Resources/Fonts/Fixedsys.ttf");
	ui_font.loadFromFile("Resources/Fonts/flappy.ttf");
	score_text.setFont(font);
	score_text.setCharacterSize(40);
	score_text.setPosition(window.getSize().x - 60, 5);
	for (int i = 0; i < 2; i++) {
		timer_text[i].setFont(font);
		timer_text[i].setCharacterSize(30 + i*10);
	}
	timer_text[0].setString("TimeLeft:");
	timer_text[0].setPosition(10, 5);
	timer_text[1].setPosition(180, -2);

	ui_text[0].setString("PRESS ENTER");
	ui_text[1].setString("TIMES UP");
	for (int i = 0; i < 2; i++) {
		ui_text[i].setFont(ui_font);
		ui_text[i].setCharacterSize(40);
		ui_text[i].setPosition(window.getSize().x / 2 - ui_text[i].getGlobalBounds().width / 2, 8);
	}


	sf::Sprite range;
	sf::Texture range_texture;
	range_texture.loadFromFile("Resources/Sprites/sample_1.png");
	range.setTexture(range_texture);
	range.setPosition(0, 60);

	float game_time = 30, game_timer = game_time;
	int gameState = 0;

	window.setMouseCursorVisible(false);
	sf::Clock clk;
	sf::Time t;
	float dt = 0, timer = 0.15;

	while (window.isOpen()) {
		t = clk.restart();
		dt = t.asSeconds();
		if (gameState == 1)
			game_timer -= dt;

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					window.close();
				if (evnt.key.code == sf::Keyboard::Enter) {
					if (gameState == 0) {
						gameState = 1;
						target.time_start.play();
					}	
					else if (gameState == 2) {
						gameState = 0;
						Score = 0;
						game_timer = game_time;
					}
				}
				break;
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
		///////////////////////////////////

		std::stringstream ss, tm;
		ss << Score;
		tm << (int)game_timer;
		score_text.setString(ss.str());
		timer_text[1].setString(tm.str());

		if (game_timer <= 0 && gameState != 2) {
			gameState = 2;
			target.time_up.play();
		}

		mousePos = sf::Mouse::getPosition(window);
		uzi.set_gun_position(mousePos);

	
		if (uzi.firing && gameState == 1) {
			if (uzi.fire_sound.getStatus() != sf::Sound::Status::Playing)
				uzi.fire_sound.play();
			uzi.fire_animation();
			if (hit_target(mousePos, target)) {
					timer -= dt;
					if (target.target_hit.getStatus() != sf::Sound::Playing)
						target.target_hit.play();
				if (timer <= 0) {
						Score++;
						target.spawn_target();
						timer = 0.15;
				}
			}
		}
		else
			uzi.gun_sprite.setTextureRect(sf::IntRect(0, 0, 160, 175));
		

		/////////////////////////////////////

		window.clear();
		window.draw(range);
		window.draw(score_text);
		for (int i = 0; i < 2; i++)
			window.draw(timer_text[i]);
		if(gameState == 0)
			window.draw(ui_text[0]);
		if(gameState == 2)
			window.draw(ui_text[1]);
		if(gameState == 1) window.draw(target.target_sprite);
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

