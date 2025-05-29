#include <iostream>

#include "Game.h"
#include "Button.h"
#include "Ball.h"

void Game::InitializeWindow()
{
    this->window = new sf::RenderWindow(this->videoMode, "GAME", sf::Style::Titlebar | sf::Style::Close);
}

void Game::InitializeVariables()
{
    this->animationStarted = false;
    this->gameIsPaused = false;
    this->videoMode.width = 1920;
    this->videoMode.height = 1080;
    this->window = nullptr;
}

void Game::InitializeGameObjects()
{
    // Buttons
    this->startButton = new Button(1500, 900, "Start");
    this->creditsOutButton = new Button(100, 900, "Credits OUT");
    this->creditsInButton = new Button(350, 900, "Credits IN");

    // Balls
    for (int i = 0; i < this->totalBalls; i++)
    {
        int randomColor = rand() % 3 + 1;
        sf::Color color;

        if (randomColor == 1)
        {
            color = sf::Color::Red;
        }
        else if (randomColor == 2)
        {
            color = sf::Color::White;
        }
        else if (randomColor == 3)
        {
            color = sf::Color::Green;
        }
        Ball *ball = new Ball(50.0f, color);
        this->balls[i] = ball;
    }

    // Information Text
    if (!this->font.loadFromFile("Font/Arial.ttf"))
        throw("ERROR FONT");

    std::string playsTextValue = std::to_string(numberOfPlays);
    this->playsText.setFont(this->font);
    this->playsText.setString("Number Of Plays: " + playsTextValue);
    this->playsText.setStyle(sf::Text::Bold);
    this->playsText.setFillColor(sf::Color::White);
    this->playsText.setCharacterSize(24);
    this->playsText.setPosition(10, 10);

    std::string creditsInTextValue = std::to_string(numberOfCreditsIn);
    this->creditsInText.setFont(this->font);
    this->creditsInText.setString("Credits In: " + creditsInTextValue);
    this->creditsInText.setStyle(sf::Text::Bold);
    this->creditsInText.setFillColor(sf::Color::White);
    this->creditsInText.setCharacterSize(24);
    this->creditsInText.setPosition(10, 60);

    std::string creditsOutTextValue = std::to_string(numberOfCreditsOut);
    this->creditsOutText.setFont(this->font);
    this->creditsOutText.setString("Credits Out: " + creditsOutTextValue);
    this->creditsOutText.setStyle(sf::Text::Bold);
    this->creditsOutText.setFillColor(sf::Color::White);
    this->creditsOutText.setCharacterSize(24);
    this->creditsOutText.setPosition(10, 110);
}

int Game::GetScreenHeight()
{
    return this->videoMode.height;
}

void Game::ResetBalls() // Reset the balls back to their starting position
{
    for (int i = 0; i < this->totalBalls; i++)
    {
        this->balls[i]->ResetBallPosition();
    }
}

bool Game::GameHasCredits() // Check if the game has credits
{
    if (this->numberOfCreditsIn > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::AllBallsFinished() // Check if all balls have finished their animation
{
    int ballCounter = 0;

    for (int i = 0; i < this->totalBalls; i++)
    {
        if (this->balls[i]->AnimationIsFinished() == true)
        {
            ballCounter++;
        }
    }

    if (ballCounter == this->totalBalls)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::UpdateCreditsInText()
{
    std::string creditsInTextValue = std::to_string(numberOfCreditsIn);
    this->creditsInText.setString("Credits In: " + creditsInTextValue);
}

void Game::UpdateCreditsOutText()
{
    std::string creditsOutTextValue = std::to_string(numberOfCreditsOut);
    this->creditsOutText.setString("Credits Out: " + creditsOutTextValue);
}

void Game::UpdateNumberOfPlays()
{
    numberOfPlays++;
    std::string playsTextValue = std::to_string(numberOfPlays);
    this->playsText.setString("Number Of Plays: " + playsTextValue);
}

void Game::IncrementCredits()
{
    this->numberOfCreditsIn++;
    UpdateCreditsInText();
}

void Game::CashoutCredits()
{
    if (this->numberOfCreditsIn > 0)
    {
        ResetBalls();
        this->numberOfCreditsOut += this->numberOfCreditsIn;
        UpdateCreditsOutText();

        this->numberOfCreditsIn = 0;
        UpdateCreditsInText();
    }
}

void Game::StartAnimation()
{
    ResetBalls();
    this->numberOfCreditsIn--;
    UpdateCreditsInText();
    this->ballCounter = 0;
    this->animationStarted = true;

    this->clock.restart();
}

void Game::UpdateAnimation()
{
    sf::Time elapsedTime = this->clock.getElapsedTime();

    if (this->ballCounter == 0) // If it is the first ball there is no need for a time delay
    {
        this->balls[this->ballCounter]->PlayAnimation();
    }
    else
    {
        if (elapsedTime.asSeconds() >= this->ballDelay.asSeconds()) // If time between each ball has passed
        {
            this->balls[this->ballCounter]->PlayAnimation();
        }
    }
    if (this->balls[this->ballCounter]->AnimationIsFinished() == true)
    {
        if (this->ballCounter < this->totalBalls - 1)
        {
            this->ballCounter++; // Set the next ball ready to play
        }
        this->clock.restart(); // Restart the clock
    }
}

void Game::DrawGameObjects()
{
    this->startButton->Draw(this->window);
    this->creditsInButton->Draw(this->window);
    this->creditsOutButton->Draw(this->window);

    this->window->draw(this->creditsInText);
    this->window->draw(this->creditsOutText);
    this->window->draw(this->playsText);

    for (int i = 0; i < totalBalls; i++)
    {
        balls[i]->Draw(this->window);
    }
}

Game::Game()
{
    this->InitializeVariables();
    this->InitializeWindow();
    this->InitializeGameObjects();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::GameIsRunning() const
{
    return this->window->isOpen();
}

void Game::Update()
{
    while (this->window->pollEvent(this->ev))
    {
        this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
        this->creditsInButton->Update(this->mousePosition);
        this->creditsOutButton->Update(this->mousePosition);
        this->startButton->Update(this->mousePosition);

        if (this->creditsInButton->IsPressed() && this->animationStarted == false) // Credits In Button
        {
            ResetBalls();
            IncrementCredits();
        }
        else if (this->startButton->IsPressed() && this->animationStarted == false) // Start Button pressed to start animation
        {
            if (GameHasCredits())
            {
                StartAnimation();
            }
        }
        else if (this->startButton->IsPressed() && this->animationStarted == true) // Start Button pressed to pause the game
        {
            this->gameIsPaused = !this->gameIsPaused;
        }
        else if (this->creditsOutButton->IsPressed() && this->animationStarted == false) // Credits Out Button
        {
            CashoutCredits();
        }

        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        default:
            break;
        }
    }

    if (this->animationStarted == true && this->gameIsPaused == false) // Only run the animation when Start button was pressed and the game is not paused
    {
        UpdateAnimation();

        if (AllBallsFinished() == true)
        {
            UpdateNumberOfPlays();
            this->animationStarted = false;
        }
    }
}

void Game::Draw()
{
    this->window->clear(sf::Color(0, 0, 255, 255));

    // Draw Game
    DrawGameObjects();

    this->window->display();
}
