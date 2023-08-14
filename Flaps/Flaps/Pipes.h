#pragma once
#include<SFML/Graphics.hpp>
class Pipes
{

public:
	Pipes(int);
	sf::Sprite sprite_up, sprite_down;
	static void loadTextures();
	void update(sf::Time& dt);
	float getRightBound();

private:
	static sf::Texture texture_down, texture_up;
	static int pipe_distance, move_speed;


};

