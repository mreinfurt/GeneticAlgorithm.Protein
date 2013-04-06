#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
 
 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic algorithms");

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
 
         
         window.clear();
		 window.display();
     }
 
     return EXIT_SUCCESS;
 }