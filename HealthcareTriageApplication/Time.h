#ifndef SENECA_TIME_H_
#define SENECA_TIME_H_
#include <iostream>
namespace seneca {
	class Time {
		unsigned int minutes;

	public:
		Time& reset();
		Time(unsigned int min = 0u);
		void write(std::ostream& ostr) const;
		void read(std::istream& istr);
		operator unsigned int()const;
		Time& operator*= (int val);
		Time& operator-= (const Time& D);
		Time operator-(const Time& T)const;
		friend std::ostream& operator<<(std::ostream& ostr, const Time& time);
		friend std::istream& operator>>(std::istream& istr, Time& time);
	};

}
#endif // !SENECA_TIME_H_