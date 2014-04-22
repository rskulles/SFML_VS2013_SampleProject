#pragma once
#include<SFML\Graphics.hpp>
#include <string>
#include <chrono>
#include <memory>

class Game
//To read more about the Game class and the conventions used
//in this file, open About_Game.txt from the solution explorer.
{
public:
	explicit Game(std::string Title);
	~Game();

	//This is what we will call in main() to run our game.
	void Run();

private://methods
	
	//The bread and butter methods of the game loop.
	void _handleEvents();
	void _update();
	void _draw();

	//Initialization
	void _initializeWindow(std::string windowName);

	//Game Updates
	void _updateTimers();
	void _updateDrawTimer();

	//Add your private methods here

private://members
	int												m_gameFramesPerSecond;//we will use this to lock are drawing to a given fps
	sf::Event										m_gameEvent;//you could call it the main event... like me.
	std::unique_ptr<sf::RenderWindow>				m_gameWindow;//The window we will draw to
	std::chrono::duration<double>					m_gameClockIteration;//Time it takes for each iteration of the game loop
	double											m_gameClockIterationTotalForDrawing;//Will keep a running total of time. Used specifically for draw updates 
	std::chrono::high_resolution_clock				m_gameClock;//The main game clock
	std::chrono::time_point<decltype(m_gameClock)>	m_gameClockStart, m_gameClockEnd;//start and end points for our clock.

	//Add your private members here
};
