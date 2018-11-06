#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <math.h>

#include <iostream>


int main()
{
	float pixelsToMeters = 20.0f;
	float angleInDegrees = 0.0f;
	sf::Vector2f acceleration;
	float e = 0.8f;
	sf::Vector2f unitVector;
	float dt = 0;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");

	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(0, 710);
	ground.setSize(sf::Vector2f{ 800,100 });

	sf::RectangleShape shape;
	shape.setSize({20.0f, 20.0f});
	shape.setFillColor(sf::Color::Green);

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(100, 690);

	sf::Vector2f gravity(0.0f, 9.8f * pixelsToMeters);

	sf::Time currentTime = { sf::seconds(0.0f) };

	sf::Text timeInAir;
	sf::Text distanceTravelled;
	sf::Font font;


	if (!font.loadFromFile("game_over.ttf"))
	{
		std::string s("Error loading texture");

		throw std::exception(s.c_str());
	}

	timeInAir.setCharacterSize(50);
	timeInAir.setFillColor(sf::Color::White);
	timeInAir.setFont(font);
	timeInAir.setPosition(50, 90);

	distanceTravelled.setCharacterSize(50);
	distanceTravelled.setFillColor(sf::Color::White);
	distanceTravelled.setFont(font);
	distanceTravelled.setPosition(50, 50);

	float m_maxHeight = 0.0f;

	sf::Clock clock;

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;



	clock.restart();

	while (window.isOpen())
	{

		//read keyboard inout
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && position.y >= 690)
			{
				velocity.y -= 80.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && velocity.x == 0)
			{
				velocity.x += 80.0f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && velocity.x == 0)
			{
				velocity.x -= 80.0f;
			}
		}

	

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{
			if (velocity.x != 0)
			{
				unitVector.x = (velocity.x / sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)));
				unitVector.y = (velocity.y / sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)));
				acceleration = -e * unitVector * pixelsToMeters;
			}
			else if (velocity.y != 0)
			{
				acceleration = gravity;
			}

			if (position.y > 690 && position.y < 690)
			{
				position.y = 690;
			}

			if (position.y + 20 <= ground.getPosition().y && velocity != sf::Vector2f{0,0})
			{
				velocity = velocity + acceleration * timeSinceLastUpdate.asSeconds();
				position = position + velocity * timeSinceLastUpdate.asSeconds() + (0.5f * acceleration * (timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds()));
				currentTime += timeSinceLastUpdate;

				timeInAir.setString("Time: " + std::to_string(currentTime.asSeconds()));
			}
			else
			{
				timeInAir.setString("Time: " + std::to_string(currentTime.asSeconds()));
			}

			if (abs(velocity.x) < 1 * pixelsToMeters)
			{
				velocity.x = 0;
			}


			window.clear();

			// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().


			//update shape on screen
			shape.setPosition(position);


			window.draw(shape);
			window.draw(ground);
			window.draw(timeInAir);
			window.draw(distanceTravelled);

			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}



	}

	return 0;
}
