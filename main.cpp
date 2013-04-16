#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include "algorithm.h"

std::string SEQ20 = "10100110100101100101";
std::string SEQ24 = "110010010010010010010011";
std::string SEQ25 = "0010011000011000011000011";
std::string SEQ36 = "000110011000001111111001100001100100";
std::string SEQ48 = "001001100110000011111111110000001100110010011111";
std::string SEQ50 = "11010101011110100010001000010001000101111010101011";

 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic algorithms - Norman Ackermann, Manuel Reinfurt");
	 window.setVerticalSyncEnabled(true);
	 Algorithm algorithm(window);	
	 algorithm.foldRandom();

     sf::Font font;
     if (!font.loadFromFile("Sansation.ttf"))
         return EXIT_FAILURE;

	 std::string energyText = "Energy: ";
	 energyText.append(std::to_string((algorithm.getEnergy())));

	 sf::Text energy(energyText, font, 20);
	 energy.setPosition(10, 5);

	 sf::Text instruction("Num 1(20), 2(25), 3(36), 4(50) - Any key: New folding", font, 20);
	 instruction.setPosition(10, 560);

	 int bestFolding = 0;
	 sf::Text bestEnergy(energyText, font, 20);
	 bestEnergy.setPosition(600, 5);

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
				if (event.key.code == sf::Keyboard::Num1)
				{
					algorithm.readProteinsFromString(SEQ20);
				}

				if (event.key.code == sf::Keyboard::Num2)
				{
					algorithm.readProteinsFromString(SEQ25);
				}

				if (event.key.code == sf::Keyboard::Num3)
				{
					algorithm.readProteinsFromString(SEQ36);
				}

				if (event.key.code == sf::Keyboard::Num4)
				{
					algorithm.readProteinsFromString(SEQ50);
				}

				if (event.key.code == sf::Keyboard::R)
				{
					bestFolding = 0;
				}
								
				algorithm.foldRandom();
				if (algorithm.getEnergy() > bestFolding)
				{
					bestFolding = algorithm.getEnergy();
					std::string energyText = "Best Energy: ";
					energyText.append(std::to_string((algorithm.getEnergy())));
					bestEnergy.setString(energyText);
				}
			 }
         }
		 
		 window.clear(sf::Color(60, 60, 60, 255));

		 std::string energyText = "Energy: ";
		 energyText.append(std::to_string((algorithm.getEnergy())));
		 energy.setString(energyText);

		 algorithm.draw();
		 window.draw(energy);
		 window.draw(bestEnergy);
		 window.draw(instruction);
		 window.display();
     }
 
     return EXIT_SUCCESS;
 }