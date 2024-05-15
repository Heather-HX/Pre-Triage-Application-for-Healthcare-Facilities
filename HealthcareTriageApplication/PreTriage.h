#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H
#include "Menu.h"
#include "Patient.h" 
#include "Time.h"
#include <cstring>

namespace seneca {
    const int maxNoOfPatients = 100;

    class PreTriage {
        Time m_averConWait;
        Time m_averTriageWait;
        Patient* m_lineup[maxNoOfPatients]{};
        char* m_dataFilename{};
     
        Menu m_appMenu;

        int m_lineupSize;
        void reg(); 
        void admit(); 
        int indexOfFirstInLine(char type) const; 

        Time setAverageWaitTime(Patient& patient);
        Time getWaitTime(Patient& patient);
        void lineup();
        void load(); 
        void save(); 
    public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run();
    };
}

#endif 