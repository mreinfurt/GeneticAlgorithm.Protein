                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             #include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <iostream>
#include "algorithm.h"

std::string SEQ20 = "10100110100101100101";
std::string SEQ24 = "110010010010010010010011";
std::string SEQ25 = "0010011000011000011000011";
std::string SEQ36 = "000110011000001111111001100001100100";
std::string SEQ48 = "001001100110000011111111110000001100110010011111";
std::string SEQ50 = "11010101011110100010001000010001000101111010101011";
std::string SEQ100 = "1101010101111010001000100001000100010111101010101111010101011110100010001000010001000101111010101011";

void testRates(Algorithm &algorithm);
 int main()
 {
	 // Camera/View attributes
	 float scale = 1.0f;
	 float moveSpeed = 15.f;
	 float scaleSpeed = 0.05f;

     sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic algorithms - Norman Ackermann, Manuel Reinfurt");
	 sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	 window.setVerticalSyncEnabled(false);

	 Algorithm algorithm(window);

     sf::Font font;
     if (!font.loadFromFile("Sansation.ttf"))
         return EXIT_FAILURE;

	 std::string energyText = "Energy: ";
	 energyText.append(std::to_string((algorithm.getEnergy())));

	 sf::Text energy(energyText, font, 20);
	 energy.setPosition(10, 5);

	 algorithm.setUp(1, SEQ20, 0.08f, 0.3f);

     while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event))
         {
			 #pragma region User Input
             if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                 window.close();

			 if (event.type == sf::Event::KeyPressed)
			 {

				if (event.key.code == sf::Keyboard::Return)
				{
					algorithm.setUp(250, SEQ20, 0.08, 0.3);
				}

				if (event.key.code == sf::Keyboard::Space)
				{
					algorithm.run(150, SEQ20, 0.12, 0.3);
				}
				 
				if (event.key.code == sf::Keyboard::R)
				{
					scale = 1.0f;
				}

				if (event.key.code == sf::Keyboard::Left)
				{
					view.move(sf::Vector2f(-moveSpeed, 0));
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					view.move(sf::Vector2f(moveSpeed, 0));
				}

				if (event.key.code == sf::Keyboard::Up)
				{
					view.move(sf::Vector2f(0, -moveSpeed));
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					view.move(sf::Vector2f(0, moveSpeed));
				}

				if (event.key.code == sf::Keyboard::Comma)
				{
					scale -= scaleSpeed;
				}
				else if (event.key.code == sf::Keyboard::Period)
				{
					scale += scaleSpeed;
				}
			 }
			#pragma endregion 
         }

		 std::string energyText = "Energy: ";
		 energyText.append(std::to_string((algorithm.getEnergy())));	
		 energy.setString(energyText);

		 // Set our camera
		 view.setViewport(sf::FloatRect(0, 0, scale, scale));

		 window.clear(sf::Color(60, 90, 130, 255));
		 window.setView(view);
			algorithm.update();
			algorithm.draw();
			window.draw(energy);
		 window.display();
     }
 
     return EXIT_SUCCESS;
 }

 void testRates(Algorithm &algorithm)
 {
	 float mutationRate = 0.04f;
	 float crossoverRate = 0.15f;

	 std::ofstream logfile;
	 logfile.open("testRates.txt");

	 for (int m = 0; m <= 9; ++m)
	 {
		 logfile << mutationRate << "\t";

		 for (int c = 0; c <= 20; ++c)
		 {
			 float average = 0;
			 float cumulativeEnergy = 0;

			 for (int i = 0; i < 15; ++i)
			 {
				 algorithm.run(1500, SEQ20, mutationRate, crossoverRate);
				 cumulativeEnergy+= algorithm.gAvg;
			 }

			 average = cumulativeEnergy / 10;
			 
			 logfile << average << "\t";
			 std::cout << mutationRate << "\t" << (crossoverRate * 2) << "\t" << average << "\t" << algorithm.gBestEnergy << "\n";

			 crossoverRate += 0.01f;
		 }

		 logfile << "\n";
		 std::cout << "\n";

		 crossoverRate = 0.15f;
		 mutationRate += 0.01f;
	 }

	 logfile.close();
 }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               