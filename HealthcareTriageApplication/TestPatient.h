#ifndef SENECA_TESTPATIENT_H
#define SENECA_TESTPATIENT_H

#include "Patient.h" 
namespace seneca {
    class TestPatient : public Patient {
    public:
        TestPatient();
        virtual char type() const override;
        virtual std::istream& read(std::istream& is) override;
        virtual std::ostream& write(std::ostream& os) const override;
    };
}
#endif 