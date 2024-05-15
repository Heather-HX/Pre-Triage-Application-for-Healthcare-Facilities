#define _CRT_SECURE_NO_WARNINGS
#include "TriagePatient.h"
#include <cstring>
#include <iostream>
using namespace std;
namespace seneca {
    int nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket++), symptoms(nullptr) {}

    TriagePatient::TriagePatient(const TriagePatient& other) : Patient(other) {
        symptoms = nullptr;
        if (other.symptoms) {
            symptoms = new char[strlen(other.symptoms) + 1];
            strcpy(symptoms, other.symptoms);
        }
    }

    TriagePatient& TriagePatient::operator=(const TriagePatient& other)
    {
        if (this != &other) {
            Patient::operator=(other); 
            delete[] symptoms;
            symptoms = nullptr;
            if (other.symptoms) {
                symptoms = new char[strlen(other.symptoms) + 1];
                strcpy(symptoms, other.symptoms);
            }
        }
        return *this;
    }

    TriagePatient::~TriagePatient() {
        delete[] symptoms;
    }

    char TriagePatient::type() const {
        return 'T';
    }

    istream& TriagePatient::read(istream& is) {
        delete[] symptoms;

        Patient::read(is);
        char tempSymptoms[512]{};
        if (&is != &cin) {
            is.ignore();
            is.getline(tempSymptoms, 511, '\n');
            nextTriageTicket = number() + 1;
        }
        else {
            cout << "Symptoms: ";
            is.getline(tempSymptoms, 511, '\n');
        }

        symptoms = new char[strlen(tempSymptoms) + 1];
        strcpy(symptoms, tempSymptoms);

        if (is.fail()) {
            delete[] symptoms;
            symptoms = nullptr;
        }

        return is;
    }

    ostream& TriagePatient::write(ostream& os) const {

        if (&os == &cout) {
            os << "TRIAGE" << endl;
            Patient::write(os);
            os << "Symptoms: " << symptoms << endl;
        }
        else if (&os == &clog) {
            Patient::write(os);

        }
        else {
            Patient::write(os);
            os << "," << symptoms;

        }
        return os;
    }
}