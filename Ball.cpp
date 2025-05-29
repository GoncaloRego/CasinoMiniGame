#include <iostream>
#include "Ball.h"

Ball::Ball(float radius, sf::Color color)
{
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
	this->shape.setPosition(sf::Vector2f(this->startingPosition_X, this->startingPosition_Y));

	this->randomDestinyPositionX = 0;
}

Ball::~Ball()
{
}

int Ball::GetPosition()
{
	return this->shape.getPosition().y;
}

void Ball::ResetBallPosition() // Reset Ball to the starting position
{
	this->shape.setPosition(sf::Vector2f(this->startingPosition_X, this->startingPosition_Y));
}

bool Ball::AnimationIsFinished() // Check if the Ball has finished its animation
{
	if (this->shape.getPosition().y <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ball::PlayAnimation()
{
	if (this->randomDestinyPositionX == 0)
	{
		this->randomDestinyPositionX = (float)rand() / (float)RAND_MAX; // Set a random X direction to each ball only once
	}

	if (randomDestinyPositionX < 0.5f) // Set the direction of the ball depending on the random result
	{
		this->shape.move(-randomDestinyPositionX * 2, -2);
	}
	else
	{
		this->shape.move(randomDestinyPositionX * 2, -2);
	}
}

void Ball::Draw(sf::RenderWindow* window)
{
	window->draw(this->shape);
}
