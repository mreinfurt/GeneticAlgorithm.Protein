#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include "algorithm.h"

 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic algorithms");
	 Algorithm algorithm(window);
	 algorithm.fillArrayRandom();

     while (window.isOpen())
     {
         // Process events
         sf::Event event;
         while (window.pollEvent(event))
         {
             // Close window : exit
             if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                 window.close();
         }
		 
		 window.clear(sf::Color(60, 60, 60, 255));
		 algorithm.draw();
		 window.display();
     }
 
     return EXIT_SUCCESS;
 }