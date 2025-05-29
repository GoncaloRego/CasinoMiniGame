#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Button
{
private:
	float textOffset = 5.0f;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	sf::Color color;
	sf::Color hoverColor;

	bool isPressed;

public: 
	Button(float x, float y, std::string buttonText);
	~Button();

	void Update(sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow* window);
	bool IsPressed();
};

