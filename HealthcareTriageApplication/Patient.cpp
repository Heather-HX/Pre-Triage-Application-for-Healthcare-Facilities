#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip> 
using namespace std;
namespace seneca {

    Patient::Patient(int ticketNumber) : m_OHIP(0), m_ticket(ticketNumber), m_fileIO(false) {
        m_name = nullptr;
    }

    Patient::Patient(const Patient& other)
        : m_OHIP(other.m_OHIP), m_ticket(other.m_ticket), m_fileIO(other.m_fileIO) {
        if (other.m_name) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        }
        else {
            m_name = nullptr;
        }
    }

    Patient::operator const char* ()const
    {
        return m_name;
    }

    Patient::operator bool() const
    {
        return m_name != nullptr && m_OHIP >= 100000000 && m_OHIP <= 999999999;
    }

    int Patient::number() const {
        return m_ticket.number();
    }
    Patient::~Patient() {
        delete[] m_name;
    }

    Patient& Patient::operator=(const Patient& other) {
        if (this != &other) {
            char* newName = nullptr;
            if (other.m_name) {
                newName = new char[strlen(other.m_name) + 1];
                strcpy(newName, other.m_name);
            }

            delete[] m_name;
            m_name = newName;
            m_OHIP = other.m_OHIP;
            m_ticket = other.m_ticket;
            m_fileIO = other.m_fileIO;
        }
        return *this;
    }

    bool Patient::operator==(char c) const {
        return type() == c;
    }

    bool Patient::operator==(const Patient& other) const {
        return type() == other.type();
    }

    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    Time Patient::time() const {
        return m_ticket.time();
    }

    ostream& Patient::write(ostream& ostr) const {
        if (&ostr == &clog) {
            if (m_name == nullptr || m_OHIP == 0) {
                ostr << "Invalid Patient Record";
            }
            else {
                ostr << left << setw(53) << setfill('.') << m_name
                    << m_OHIP
                    << right << setw(5) << setfill(' ') << m_ticket.number() << " "
                    << m_ticket.time();
            }
        }
        else if (&ostr == &cout) {

            if (m_name == nullptr || m_OHIP == 0) {
                ostr << "Invalid Patient Record" << endl;
            }
            else {
                ostr << "Ticket No: " << m_ticket.number() << ", Issued at: " << m_ticket.time() << endl
                    << m_name << ", OHIP: " << m_OHIP << endl;
            }
        }
        else {
            ostr << type() << ',' << (m_name ? m_name : "") << ',' << m_OHIP << ',';
            m_ticket.write(ostr);
        }
        return ostr;
    }

    istream& Patient::read(istream& istr) {
        char tempName[51];
        if (&istr == &cin) {
            istr.ignore(1000, '\n');
            cout << "Name: ";
            istr.get(tempName, 51);
            istr.clear();
            istr.ignore(1000, '\n');

            delete[] m_name;
            m_name = new char[strlen(tempName) + 1];
            strcpy(m_name, tempName);

            cout << "OHIP: ";
            while (!(istr >> m_OHIP) || m_OHIP < 100000000 || m_OHIP > 999999999) {
                cout << (istr.fail() ? "Bad integer value, try again: " : "Invalid value enterd, retry[100000000 <= value <= 999999999]: ");
                istr.clear();
                istr.ignore(1000, '\n');
            }
            istr.ignore(1000, '\n');
        }
        else {
            istr.get(tempName, 51, ',');
            istr.ignore(1000, ',');

            delete[] m_name;
            m_name = new char[strlen(tempName) + 1];
            strcpy(m_name, tempName);
            istr >> m_OHIP;
            istr.ignore(1000, ',');
            m_ticket.read(istr);
        }
        return istr;
    }

    const char* Patient::getName() const {
        return m_name;
    }
}