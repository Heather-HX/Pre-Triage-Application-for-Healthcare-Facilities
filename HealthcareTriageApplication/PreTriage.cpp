#define _CRT_SECURE_NO_WARNINGS
#include "PreTriage.h"
#include "Patient.h"
#include "TestPatient.h"
#include "TriagePatient.h" 
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

namespace seneca {
    PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup\n0- Exit\n> "),
        m_lineupSize(0) {
        for (int i = 0; i < maxNoOfPatients; ++i) {
            m_lineup[i] = nullptr;
        }
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        load();
    }

    PreTriage::~PreTriage() {
        save();
        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i] != nullptr) {
                delete m_lineup[i];
                m_lineup[i] = nullptr;
            }
        }
        delete[] m_dataFilename;
    }

    void PreTriage::run() {
        int selection;
        do {
            m_appMenu >> selection;
            switch (selection) {
            case 1:
                reg();
                break;
            case 2:
                admit();
                break;
            case 3:
                lineup();
                break;
            case 0:
                break;
            default:
                cout << "Invalid option selected. Please try again." << endl;
                break;
            }
        } while (selection != 0);
    }

    void PreTriage::load() {
        ifstream file(m_dataFilename);
        cout << "Loading data..." << endl;
        if (!file || file.fail()) {
            cout << "No data or bad data file!\n" << endl;
            m_averConWait = 15;
            m_averTriageWait = 5;
        }
        else {
            file >> m_averConWait;
            file.ignore(1000, ',');
            file >> m_averTriageWait;
            file.ignore(1000, '\n');
            Patient* localP{};
            char type = '\0';
            for (int i = 0; i < maxNoOfPatients && file >> type; ++i) {
                file.ignore(1000, ',');
                if (type == 'C') {
                    localP = new TestPatient;
                }
                else if (type == 'T') {
                    localP = new TriagePatient;
                }

                if (localP) {
                    file >> *localP;
                    m_lineup[m_lineupSize++] = localP;
                }
            }
            if (!file.eof()) {
                cout << "Warning: number of records exceeded 100" << endl;
                cout << m_lineupSize << " Records imported...\n" << endl;
            }
            else if (m_lineupSize > 0) {
                cout << m_lineupSize << " Records imported...\n" << endl;
            }
            else {
                cout << "No data or bad data file!\n" << endl;
            }
        }
        file.close();
    }

    void PreTriage::save() {
        ofstream file(m_dataFilename);
        cout << "Saving lineup..." << endl;
        if (file) {
            file << m_averConWait << "," << m_averTriageWait << endl;
            int cntCon = 0, cntTriage = 0;
            for (int i = 0; i < m_lineupSize; ++i) {
                m_lineup[i]->write(file) << endl;
                // Count types
                if (m_lineup[i]->type() == 'C') {
                    ++cntCon;
                }
                else if (m_lineup[i]->type() == 'T') {
                    ++cntTriage;
                }
            }
            cout << cntCon << " Contagion Tests and " << cntTriage << " Triage records were saved!" << endl;
        }
        file.close();
    }

    void PreTriage::lineup() {
        int selection;
        int lineNumber = 1;
        Menu lineupMenu("   Select The Lineup:\n   1- Contagion Test\n   2- Triage\n   0- Exit\n   > ");

        do {
            lineupMenu >> selection;
            switch (selection) {
            case 1: // Contagion
            {
                bool hasContagionPatients = false;
                cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
                cout << "-------------------------------------------------------------------------------\n";

                for (int i = 0; i < m_lineupSize; ++i) {
                    if (m_lineup[i] && m_lineup[i]->type() == 'C') {                       
                       clog << lineNumber++ << "   - "; 
                        m_lineup[i]->write(clog) <<  endl;                       
                        hasContagionPatients = true;
                    }
                }
                if (!hasContagionPatients) {
                    cout << "Line up is empty!\n";
                }
                cout << "-------------------------------------------------------------------------------\n";
            }
            return;
            case 2: // Triage
            {
                bool hasTriagePatients = false;
                cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
                cout << "-------------------------------------------------------------------------------\n";
                for (int i = 0; i < m_lineupSize; ++i) {
                    if (m_lineup[i] != nullptr && m_lineup[i]->type() == 'T') {              
                        clog << lineNumber++ << "   - ";
                        m_lineup[i]->write(clog) << endl;
                        hasTriagePatients = true;
                    }
                }
                if (!hasTriagePatients) {
                    cout << "Line up is empty!\n";
                }
                cout << "-------------------------------------------------------------------------------\n";
            }
            return; 
            case 0: 
                break;
            default:
                cout << "Invalid option selected. Please try again." << endl;
                break;
            }
        } while (selection != 0);
    }

    int PreTriage::indexOfFirstInLine(char type) const {
        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i] && *m_lineup[i] == type) { 
                return i;
            }
        }
        return -1; 
    }

    Time PreTriage::setAverageWaitTime(Patient& patient)
    {  
        int CT = U.getTime(); 
        int PTT = patient.time();
        int PTN = patient.number(); 
            
        Time& AWT = (patient.type() == 'C') ? m_averConWait : m_averTriageWait;
        AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
        return AWT;
    }

    void PreTriage::reg() {
        if (m_lineupSize >= maxNoOfPatients) {
            cout << "Line up full!" << endl;
            return;
        }

        Menu regMenu("   Select Type of Registration:\n   1- Contagion Test\n   2- Triage\n   0- Exit\n   > ");
        int selection = 0;
        regMenu >> selection;

        if (selection == 0) {
            return;
        }

        Patient* patient = nullptr;
        if (selection == 1) {
            patient = new TestPatient; // Instantiate a Contagion Test Patient
        }
        else if (selection == 2) {
            patient = new TriagePatient; // Instantiate a Triage Patient
        }

        if (patient != nullptr) {
            patient->setArrivalTime(); 

            cout << "Please enter patient information: " << endl;
            patient->read(cin);
            cout << endl;

            // Print the ticket
            cout << "******************************************" << endl;
            patient->write(cout);
            cout << "Estimated Wait Time: ";
            cout << getWaitTime(*patient) << endl; 
            cout << "******************************************" << endl << endl;

            m_lineup[m_lineupSize] = patient; 
            m_lineupSize++; 
        }
    }

    void PreTriage::admit() {
        Menu admitMenu("   Select Type of Admittance:\n   1- Contagion Test\n   2- Triage\n   0- Exit\n   > ");
        int selection;
        admitMenu >> selection;
        if (selection == 0) {
            return; 
        }

        char type = (selection == 1) ? 'C' : 'T';
        int index = indexOfFirstInLine(type);

        if (index == -1) {
            cout << "Lineup is empty!\n";
            return; 
        }
            
        Time call;
             
        cout << "\n******************************************\n";
        cout << "Call time:";
        cout << " [";
        call.reset().write(cout);
        cout << "]\n";
        cout << "Calling at for ";
        m_lineup[index]->write(cout); 
        cout << "******************************************\n\n";
        setAverageWaitTime(*m_lineup[index]);
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }

    Time PreTriage::getWaitTime(Patient& patient) {
        int count = 0; 
        char type = patient.type(); 

        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i] && m_lineup[i]->type() == type) {
                ++count;
            }
        }
        const Time& AWT = (type == 'C') ? m_averConWait : m_averTriageWait;

        Time totalWaitTime = AWT * count;
        return totalWaitTime;
    }

}