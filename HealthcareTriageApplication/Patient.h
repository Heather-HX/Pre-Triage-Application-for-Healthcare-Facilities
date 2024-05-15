#ifndef SENECA_PATIENT_H_
#define SENECA_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"
#include <cstring>

namespace seneca {
    class Patient : public IOAble {
        char* m_name{};
        int m_OHIP;
        Ticket m_ticket;
        bool m_fileIO;

    public:
        Patient(int ticketNumber = 0);
        Patient(const Patient& other);
        Patient& operator=(const Patient& other);
        virtual ~Patient();
        virtual char type() const = 0;

        bool operator==(char c) const;
        bool operator==(const Patient& other) const;
        void setArrivalTime();
        int number() const;
        Time time() const;

        operator const char* () const;
        operator bool() const;

        virtual std::ostream& write(std::ostream& ostr) const override;
        virtual std::istream& read(std::istream& istr) override;

    protected:
        const char* getName() const;
    };
}
#endif 