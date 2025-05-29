#include <iostream>
#include "Button.h"

Button::Button(float x, float y, std::string buttonText)
{
	if (!font.loadFromFile("Font/Arial.ttf"))
		throw("FONT ERROR");

	this->isPressed = false;
	this->hoverColor = sf::Color(173, 177, 184, 255);
	this->color = sf::Color::White;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(200, 100));
	this->shape.setFillColor(this->color);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(2.0f);

	this->text.setFont(this->font);
	this->text.setString(buttonText);
	this->text.setStyle(sf::Text::Bold);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(24);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2 - this->textOffset,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2 - this->textOffset);
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->text);
}

bool Button::IsPressed()
{
	return this->isPressed;
}

void Button::Update(sf::Vector2f mousePosition)
{
	if (this->shape.getGlobalBounds().contains(mousePosition)) // Check if mouse is "inside" the button
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Check if the mouse clicked
		{
			this->shape.setFillColor(this->hoverColor); // Change button color
			this->isPressed = true;
		}
		else
		{
			this->shape.setFillColor(this->color);
			this->isPressed = false;
		}
	}
}
