#include "Bird.h"
#include"Globals.h"


Bird::Bird() :
	gravity(10),
	flapspeed(250),
	anim_counter(0),
	texture_switch(1),
	should_fly(false)

{
	textures[0].loadFromFile("assets/birddown.png");
	textures[1].loadFromFile("assets/birdup.png");

	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR,SCALE_FACTOR);
	resetBirdPosition();
}

void Bird::setShouldFly(bool should_fly)
{
	this->should_fly = should_fly;
}
void Bird::flapBird(sf::Time &dt)
{
	velocity_y = -flapspeed * dt.asSeconds();
}
void Bird::resetBirdPosition()
{
	bird_sprite.setPosition(100, 50);
	velocity_y = 0;
}
void Bird::update(sf::Time&dt)
{
	if (bird_sprite.getGlobalBounds().top < 548 && should_fly) {
		if (anim_counter == 5) {
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch)
			{
				texture_switch = 0;
			}
			else
			{
				texture_switch=1;
				

			}
			anim_counter = 0;
		}
		anim_counter++;

		velocity_y += gravity * dt.asSeconds();
		bird_sprite.move(0,velocity_y);

		if (bird_sprite.getGlobalBounds().top < 0) {
			bird_sprite.setPosition(100,0);
		}

	}
}
float Bird::getRightBound()
{
	
	return bird_sprite.getGlobalBounds().left+bird_sprite.getGlobalBounds().width;
}
	 