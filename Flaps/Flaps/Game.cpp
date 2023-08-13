// do we even need comments
// Samyog GC ACE078BCT060
// Sujal Prasad Singh ACE078BCT076


#include "Game.h"
#include"Globals.h"
#include<iostream>
#include<SFML/Audio.hpp>
#include<sstream>
struct Sounds {
	sf::SoundBuffer chingBuffer;
	sf::SoundBuffer hopBuffer;
	sf::SoundBuffer dishkBuffer;
	sf::Sound ching;
	sf::Sound hop;
	sf::Sound dishk;
} sounds;
Game::Game(sf::RenderWindow& window): win(window), is_enter_pressed(false),
run_game(true),pipe_counter(71), pipe_spawn_time(70),score(0), start_monitoring(false),high_score(0)
{
	win.setFramerateLimit(70);
	bg_texture.loadFromFile("assets/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR,SCALE_FACTOR);
	bg_sprite.setPosition(0.f,-250.f);

	ground_texture.loadFromFile("assets/ground.png");
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);

	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_sprite1.setPosition(0, 578);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);

	font.loadFromFile("assets/flappy.ttf");
	restart_text.setFont(font);
	restart_text.setCharacterSize(28);
	restart_text.setFillColor(sf::Color::White);
	restart_text.setPosition(55, 650);
	restart_text.setString("GAME OVER! CLICK HERE TO RESTART");


	score_text.setFont(font);
	score_text.setCharacterSize(24);
	score_text.setFillColor(sf::Color::White);
	score_text.setPosition(18, 18);
	score_text.setString("SCORE: 0");

	high_score_text.setFont(font);
	high_score_text.setCharacterSize(24);
	high_score_text.setFillColor(sf::Color::White);
	high_score_text.setPosition(300, 18);
	high_score_text.setString("HIGH SCORE: 0");
	Pipes::loadTextures();

	sounds.chingBuffer.loadFromFile("assets/sfx/score.wav");
	sounds.hopBuffer.loadFromFile("assets/sfx/flap.wav");
	sounds.dishkBuffer.loadFromFile("assets/sfx/dead.wav");
	sounds.ching.setBuffer(sounds.chingBuffer);
	sounds.hop.setBuffer(sounds.hopBuffer);
	sounds.dishk.setBuffer(sounds.dishkBuffer);
}

void Game::startGameLoop()

{	
	sf::Clock clock;

	while (win.isOpen())
	{
		sf::Time dt = clock.restart();

		sf::Event event;
	
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				win.close();
			}
			if (event.type == sf::Event::KeyPressed && run_game) {
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed) {
					is_enter_pressed = true;
					std::cout << "true";
					bird.setShouldFly(true);
				}
				if (event.key.code == sf::Keyboard::Space && is_enter_pressed) {
					bird.flapBird(dt);
					sounds.hop.play();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{

				if (restart_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					restartGame();
				}

			}
		}



		doProcessing(dt);

		draw();
		win.display();
	}
}
void Game::draw()
{
	win.draw(bg_sprite);
	for (Pipes& pipes : pipes) {
		win.draw(pipes.sprite_down);
		win.draw(pipes.sprite_up);
	}
	win.draw(ground_sprite1);
	win.draw(ground_sprite2);
	win.draw(bird.bird_sprite);
	win.draw(high_score_text);
	win.draw(score_text);
	if (!run_game) {
		win.draw(restart_text);
	}

}
void Game::moveGround(sf::Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);
	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0) {
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 578);
	}
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0) {
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 578);
	}

}

void Game::doProcessing(sf::Time& dt)
{
	if (is_enter_pressed) {
		moveGround(dt);
		if (pipe_counter > pipe_spawn_time) {
			pipes.push_back(Pipes(dist(rd)));
			pipe_counter = 0;
		}
		pipe_counter++;

		for (int i = 0; i < pipes.size(); i++) {
			pipes[i].update(dt);
			if (pipes[i].getRightBound() < 0) {
				pipes.erase(pipes.begin() + i);
			}

		}
		checkCollisions();
		checkScore();
	}
	bird.update(dt);
}


void Game::checkCollisions()
{
	if (pipes.size() > 0) {
		if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			pipes[0].sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			bird.bird_sprite.getGlobalBounds().top >= 540)
			{
				is_enter_pressed = false;
				run_game = false;
				sounds.dishk.play();
			}
	}
}
void Game::checkScore()
{
	if (pipes.size()>0) {
		if (!start_monitoring) {
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_down.getGlobalBounds().left && bird.getRightBound() < pipes[0].getRightBound()) {
				start_monitoring = true;
			}
		}
			else {
				if (bird.bird_sprite.getGlobalBounds().left > pipes[0].getRightBound()) {
					score++;
					sounds.ching.play();
					score_text.setString("Score: "+toString(score));
					start_monitoring = false;
				}
			}
		

	}
}
void Game::restartGame()
{
	bird.resetBirdPosition();
	bird.setShouldFly(false);
	run_game = true;
	is_enter_pressed = false;
	pipe_counter = 71;
	pipes.clear();
	if (score > high_score) {
		high_score_text.setString("High Score: " + toString(score));
		high_score = score;
	}
	score = 0;
	score_text.setString("Score: 0");
}

std::string Game::toString(int num)
{
	std::stringstream ss;
	ss << num;

	return ss.str();
}
