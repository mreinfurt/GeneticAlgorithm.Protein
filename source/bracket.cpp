#include "bracket.h"
#include "conformation.h"

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
Bracket::Bracket() : m_HasFought(false), m_Attendee1(NULL,false), m_Attendee2(NULL,false)
{
    
}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
Bracket::~Bracket()
{
    
}

/// <summary>
/// Sets the attendees.
/// </summary>
/// <param name="attendee1">The attendee1.</param>
/// <param name="attendee2">The attendee2.</param>
void Bracket::setAttendees(Conformation &attendee1, Conformation &attendee2)
{
    m_Attendee1.first = &attendee1;
    m_Attendee2.first = &attendee2;
}

/// <summary>
/// Lets the two attendees fight. 
/// </summary>
/// <param name="winrate">The winrate of the attendee with the higher energy value.</param>
void Bracket::fight(float winrate)
{
	if ( m_Attendee1.first->getEnergy() > m_Attendee2.first->getEnergy() )
    {
        if (((rand() % 100)+1) <= winrate) {
            m_Attendee1.second = true;
        }
        else
        {
            m_Attendee2.second = true;
        }
    }
    else
    {
        if (((rand() % 100)+1) <= winrate) {
            m_Attendee2.second = true;
        }
        else
        {
            m_Attendee1.second = true;
        }
    }
    
    m_HasFought = true;
}

/// <summary>
/// Returns the winner of this bracket.
/// </summary>
/// <returns></returns>
Conformation& Bracket::getWinner(void)
{
    
    if (m_Attendee1.second == true) {
        return *m_Attendee1.first;
    }
    else if (m_Attendee2.second == true)
    {
        return *m_Attendee2.first;
    }
    else
    {
        throw -1;
    }
}

/// <summary>
/// Returns the loser of this bracket.
/// </summary>
/// <returns></returns>
Conformation& Bracket::getLoser(void)
{
    if (!m_HasFought) {
        throw -1;
    }
    else if (m_Attendee1.second == false)
    {
        return *m_Attendee1.first;
    }
    else
    {
        return *m_Attendee2.first;
    }
}