#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Ball
{
private:
	sf::CircleShape shape;
	float randomDestinyPositionX;
	int startingPosition_X = 960;
	int startingPosition_Y = 1100;

public:
	Ball(float radius, sf::Color color);
	~Ball();

	int GetPosition();
	void ResetBallPosition();
	bool AnimationIsFinished();
	void PlayAnimation();
	void Draw(sf::RenderWindow* window);
};

