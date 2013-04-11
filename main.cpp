#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include "algorithm.h"

 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic algorithms");
	 window.setVerticalSyncEnabled(true);
	 Algorithm algorithm(window);
	 
	 algorithm.readProteinsFromString("10110010101100100");
	 algorithm.foldRandom();

     sf::Font font;
     if (!font.loadFromFile("Sansation.ttf"))
         return EXIT_FAILURE;

	 std::string energyText = "Energy: ";
	 energyText.append(std::to_string((algorithm.getEnergy())));

	 sf::Text energy(energyText, font, 20);
	 energy.setPosition(10, 10);

	 sf::Text instruction("Press space to generate new folding", font, 20);
	 instruction.setPosition(10, 560);

     while (window.isOpen())
     {
         // Process events
         sf::Event event;
         while (window.pollEvent(event))
         {
             // Close window : exit
             if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                 window.close();

			 if (event.type == sf::Event::KeyPressed)
			 {
				if (event.key.code == sf::Keyboard::Space)
				{
					algorithm.foldRandom();
				}
			 }
         }
		 
		 window.clear(sf::Color(60, 60, 60, 255));
		 algorithm.draw();
		 window.draw(energy);
		 window.draw(instruction);
		 window.display();
     }
 
     return EXIT_SUCCESS;
 }