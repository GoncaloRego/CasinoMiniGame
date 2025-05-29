// Fabamaq_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main()
{
    Game game;

    // Game Loop
    while (game.GameIsRunning())
    {
        game.Update();
        game.Draw();
    }

    return 0;
}
