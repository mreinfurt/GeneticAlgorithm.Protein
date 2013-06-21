#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <iostream>
#include "algorithm.h"
#include "tournamentSelection.h"
#include "bestWinsTournament.h"
#include "probabilityTournament.h"

std::string SEQ20 = "10100110100101100101";
std::string SEQ24 = "110010010010010010010011";
std::string SEQ25 = "0010011000011000011000011";
std::string SEQ36 = "000110011000001111111001100001100100";
std::string SEQ48 = "001001100110000011111111110000001100110010011111";
std::string SEQ50 = "11010101011110100010001000010001000101111010101011";
std::string SEQ60 = "001110111111110001111111111010001111111111110000111111011010";	// 60	36
std::string SEQ64 = "1111111111110101001100110010011001100100110011001010111111111111";	// 64	42
std::string SEQ85 = "1111000011111111111100000011111111111100011111111111100011111111111100010011001100101"; // 85	53
std::string SEQ100 = "0001100111100111011011011110000000011111100111111000000000101101111111111100111011010010111000000111"; // 100	50
std::string SEQ100_2 = "0000001011000001110111110110000110011011111011111111110110111111100000000000111111100101110000001011"; // 100	48

void testTournaments(Algorithm &algorithm);
void testRates(Algorithm &algorithm);
 int main()
 {
	 // Camera/View attributes
	 float scale = 1.0f;
	 float moveSpeed = 15.f;
	 float scaleSpeed = 0.05f;

     sf::RenderWindow window(sf::VideoMode(1024, 600), "Genetic algorithms - Norman Ackermann, Manuel Reinfurt");
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

	 algorithm.setUp(20, 5000, SEQ48, 0.08f, 0.30f, new TournamentSelection(2.0f, 0.8f));
	 algorithm.run(true);

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
					algorithm.setUp(500, 5000, SEQ36, 0.08, 0.30f, new TournamentSelection(2.0, 80.0f));
				}

				if (event.key.code == sf::Keyboard::Space)
				{
					algorithm.setUp(500, 5000, SEQ36, 0.08f, 0.30f, new BestWinsTournament(2));
					algorithm.run(true);
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

 void testTournaments(Algorithm &algorithm)
 {
	 std::ofstream logfile("tournamentTest.txt");

	 int tournamentSize = 2;
	 int generations = 250;
	 int populationSize = 5000;

	 float mutationRate = 0.08f;
	 float crossoverRate = 0.6f;

	 for (int k = tournamentSize; k < populationSize; ++k)
	 {
		 algorithm.setUp(generations, populationSize, SEQ48, mutationRate, crossoverRate / 2.0f, new BestWinsTournament(k));
		 algorithm.run(false);

		 float average = algorithm.getAverageFitness();
		 logfile << k << "\t" << average << "\t" << "\n";
		 std::cout << k << "\t" << average << "\t" << std::endl;
	 }

	 logfile.close();
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

			 for (int i = 0; i < 10; ++i)
			 {
				 algorithm.setUp(500, 5000, SEQ50, mutationRate, crossoverRate, new TournamentSelection(2, 80));
				 algorithm.run(false);
				 cumulativeEnergy += algorithm.getAverageFitness();
			 }

			 average = cumulativeEnergy / 10;
			 
			 logfile << average << "\t";
			 std::cout << mutationRate << "\t" << (crossoverRate * 2) << "\t" << average << "\t" << algorithm.getBestEnergy() << "\n";

			 crossoverRate += 0.01f;
		 }

		 logfile << "\n";
		 std::cout << "\n";

		 crossoverRate = 0.15f;
		 mutationRate += 0.01f;
	 }

	 logfile.close();
 }