#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H
#include <iostream>

namespace seneca {

    class IOAble {
    public:
        // Pure virtual functions
        virtual std::ostream& write(std::ostream& ostr) const = 0;
        virtual std::istream& read(std::istream& istr) = 0;

        // Virtual destructor
        virtual ~IOAble();

        // Friend operator overloads
        friend std::ostream& operator<<(std::ostream& ostr, const IOAble& io);
        friend std::istream& operator>>(std::istream& istr, IOAble& io);
    };

}

#endif