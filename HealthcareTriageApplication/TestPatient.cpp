#include "TestPatient.h"
using namespace std;
namespace seneca {
    int nextTestTicket = 1;

    TestPatient::TestPatient() : Patient(nextTestTicket++) {}

    char TestPatient::type() const {
        return 'C';
    }

    istream& TestPatient::read(istream& is) {
        Patient::read(is);
        if (&is != &cin) {
            nextTestTicket = Patient::number() + 1;
        }
        return is;
    }

    ostream& TestPatient::write(ostream& os) const {
        if (&os == &cout) {
            os << "Contagion TEST" << endl;
        }
        Patient::write(os);
        return os;
    }
}