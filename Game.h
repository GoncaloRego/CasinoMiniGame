#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Button.h"
#include "Ball.h"

class Game
{
private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Objects
	Button *startButton;
	Button *creditsInButton;
	Button *creditsOutButton;
	Ball *balls[50];
	Ball *newBall;

	sf::Text creditsInText;
	sf::Text creditsOutText;
	sf::Text playsText;

	sf::Font font;

	sf::Vector2f mousePosition;

	bool gameIsPaused;

	int numberOfCreditsIn = 0;
	int numberOfCreditsOut = 0;
	int numberOfPlays = 0;
	int totalBalls = 50;

	bool animationStarted;
	int ballCounter = 0;

	sf::Clock clock;
	sf::Time ballDelay = sf::microseconds(50000);

	void InitializeWindow();
	void InitializeVariables();
	void InitializeGameObjects();

	void ResetBalls();
	bool GameHasCredits();
	bool AllBallsFinished();
	void UpdateCreditsInText();
	void UpdateCreditsOutText();
	void UpdateNumberOfPlays();

	void UpdateAnimation();

	void DrawGameObjects();

public:
	Game();
	virtual ~Game();

	const bool GameIsRunning() const;

	int GetScreenHeight();
	void IncrementCredits();
	void CashoutCredits();
	void StartAnimation();

	void Update();
	void Draw();
};
