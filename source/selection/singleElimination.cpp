#include "singleElimination.h"
#include "../bracket.h"
#include <math.h>

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="size">The size.</param>
/// <param name="winRate">The win rate.</param>
SingleElimination::SingleElimination(int size, int winRate) : m_TournamentSize(size), m_WinRate(winRate)
{

}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
SingleElimination::~SingleElimination(void)
{

}

/// <summary>
/// Selects a number of conformation from the given conformations vector.
/// This is done using by using the single elimination method.
/// </summary>
/// <param name="conformations">The conformations.</param>
void SingleElimination::select(std::vector<Conformation> &conformations)
{
	// k only 2,4,8,16,32,64 ...
	std::vector<Conformation> selectedFoldings;
	std::vector<Conformation> &foldings = conformations;

	unsigned int runden;
	if (std::pow(2,7) <= m_TournamentSize)
	{
		runden = 7;
	}
	else if (std::pow(2,6) <= m_TournamentSize)
	{
		runden = 6;
	}
	else if (std::pow(2,5) <= m_TournamentSize)
	{
		runden = 5;
	}
	else if (std::pow(2,4) <= m_TournamentSize)
	{
		runden = 4;
	}
	else if (std::pow(2,3) <= m_TournamentSize)
	{
		runden = 3;
	}
	else if (std::pow(2,2) <= m_TournamentSize)
	{
		runden = 2;
	}
	else if (std::pow(2,1) <= m_TournamentSize)
	{
		runden = 1;
	}
	else
	{
		throw -1;
	}
		
	for (unsigned int i=0; i<foldings.size(); ++i)
	{
		std::vector<Conformation> attendees;
		// Teilnehmer ziehen
		for (unsigned int j=0; j < m_TournamentSize; ++j)
		{
			Conformation& randomFolding = foldings.at(rand() % foldings.size());
			attendees.push_back(randomFolding);
		}
	
		for (unsigned int i=0; i<runden; ++i)
		{
			std::vector<Conformation> newAttendees;
	
			for (unsigned int j=0; j<attendees.size(); j+=2)
			{
				Bracket myBracket;
				myBracket.setAttendees(attendees.at(j),attendees.at(j+1));
				myBracket.fight(m_WinRate);
	
				newAttendees.push_back(myBracket.getWinner());
			}
			attendees = newAttendees;
		}

		selectedFoldings.push_back(attendees.at(0)); // Der letzte ueberlebende wird selektiert
	}

	foldings = selectedFoldings;
}