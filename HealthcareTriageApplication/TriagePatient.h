#ifndef SENECA_TRIAGEPATIENT_H
#define SENECA_TRIAGEPATIENT_H
#include "Patient.h" 
namespace seneca {
    class TriagePatient : public Patient {
        char* symptoms{};
    public:
        TriagePatient();
        TriagePatient(const TriagePatient& other); 
        TriagePatient& operator=(const TriagePatient& other); 
        ~TriagePatient();

        virtual char type() const override;
        virtual std::ostream& write(std::ostream& os) const override;
        virtual std::istream& read(std::istream& is) override;
    };
}
#endif 