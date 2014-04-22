#include "Game.h"

Game::Game(std::string Title)
{
	_initializeWindow(Title);
	m_gameFramesPerSecond=60;//Game Will draw at this frame rate
	m_gameClockIterationTotalForDrawing = 0;
	//Add any other initialization code here
}

Game::~Game()
{
	//Add your shutdown code here
}

void Game::_initializeWindow(std::string Title)
{
	//Create some variables to get the desktop dimensions and make window setup easier.
	sf::VideoMode desktopDimensions(sf::VideoMode::getDesktopMode());//Copy constructor for sf::VideoMode, using the static method of the sf::VideoMode class to initialize it;
	float dimensionMultiplier(0.90f);//How big the window is going to be compared to the desktop. 90% by default
	int windowWidth=static_cast<int>(desktopDimensions.width*dimensionMultiplier); //desktopWidth x multiplier=the width of the window
	int windowHeight = static_cast<int>(desktopDimensions.height*dimensionMultiplier);//desktopHeight x multiplier=the height of the window

	//Create a new window using the modern C++ make_unique method this is the only pointer the base code uses
	m_gameWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowWidth,windowHeight),Title);
	
	//Set the window position
	sf::Vector2<int> windowPosition(static_cast<int>(desktopDimensions.width*0.05), 0);//the setPosition method needs a sf::Vector2i note: mathematics vector not std C++ vector
	m_gameWindow->setPosition(windowPosition);//use the newly created vector to set the window position. Notice the use of -> as m_gameWindow is a pointer. 

	//as an excersise you can try squasing the code down into 2 lines or figure out how to get rid of this method entirely and not use pointers. Either is possible.
}

void Game::Run()
//This is the main gamme loop. Changes to this code should be few and far between
{
	while (m_gameWindow->isOpen())
	{
		m_gameClockStart = m_gameClock.now();

		//The bread and butter methods
		_handleEvents();
		_update();
		_draw();

		m_gameClockEnd = m_gameClock.now();
		m_gameClockIteration = m_gameClockEnd - m_gameClockStart;
	}

}

void Game::_handleEvents()
/*
	The handleEvents method should just be used as a wrapper for 
	the events you want to handle. Here a switch statement is used
	to dispatch the event type to the correct method to handle it.
	You can erase it and put a giant nested if else web of suck here
	like I did for my first toy game. It's not fun managing one of those,
	trust me. The dispatchers will proabaly lead to more switch statements
	with more dispatchers, but the cognitive load will be much easier to 
	deal with.
*/
{
	while (m_gameWindow->pollEvent(m_gameEvent))
	{
		switch (m_gameEvent.type)
		{
		case sf::Event::KeyPressed:
			//Add an event handler here. like _myHandleKeyDown();
			break;
		case sf::Event::KeyReleased:
			//Add an event handler here like _myHandleKeyUp();
			break;
		case sf::Event::Closed:
			//One of the only events that really doesn't need a handler
			m_gameWindow->close();
			break;
		default:
			break;
		}
	}
}


void Game::_update()
/*
	The update method should just be used as a wrapper for 
	the update methods of other game objects. Again, writing
	a bunch of smaller functions takes the cognitive load off
	of writing one huge update.
*/
{
	_updateTimers();

	//Add your updates here
}

void Game::_draw()
/*
	Main drawing function for the game
*/
{
	if (m_gameClockIterationTotalForDrawing>=static_cast<double>(1.0/m_gameFramesPerSecond))
	{
		m_gameWindow->clear();
		//Put your calls to m_gameWindow->draw() here
		m_gameWindow->display();
	}

	//as an exercise you can change the color the background clears to by adding a sf::Color to m_gameWindow->clear(sf::Color) try
	//changing the color to red, green, or blue.
}

void Game::_updateTimers()
//updateTimers manage the state for all the timers you need
{
	_updateDrawTimer();
	//Handle your timers here
}

void Game::_updateDrawTimer()
/*
	Manages the timer that controls the display of graphics
*/
{
	//We are only drawing the frame 1/m_gameFramesPerSecond once the timer is or exceeds that time we should clear it
	if (m_gameClockIterationTotalForDrawing >= static_cast<double>(1.0 / m_gameFramesPerSecond))
	{
		m_gameClockIterationTotalForDrawing = 0;
	}
	//Add the current iteration time to the timer
	m_gameClockIterationTotalForDrawing += m_gameClockIteration.count();

	//as an excersise you can get rid of of handling timers yourself and create a timer class with a TimerClass.Update() method.
	//A timer class will allow you to keep timers in containers like map, array, map, vector, map, map, and map. (Which container do you think I'd prefer?)
}