#ifndef BRACKET_H
#define BRACKET_H

#include <utility>

class Conformation;
class Bracket {
public:
    Bracket();
    ~Bracket();
    void setAttendees(Conformation &attendee1, Conformation &attendee2);
    void fight(float winrate);
    Conformation& getWinner(void);
    Conformation& getLoser(void);
    
private:
    std::pair<Conformation*, bool> m_Attendee1;
    std::pair<Conformation*, bool> m_Attendee2;
    
    bool m_HasFought;    
};


#endif

