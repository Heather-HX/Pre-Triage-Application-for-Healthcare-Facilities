#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace seneca {

	Time::Time(unsigned int min)
	{
		minutes = min;
	}

	Time& Time::reset()
	{
		minutes = U.getTime();
		return *this;
	}

	void Time::write(std::ostream& ostr) const
	{
		unsigned int hrs;
		unsigned int mins;
		hrs = minutes / 60;
		mins = minutes % 60;
		ostr << setw(2) << setfill('0') << hrs << ":"
			<< setw(2) << setfill('0') << mins;
	}

	void Time::read(std::istream& istr)
	{
		unsigned int hrs = 0, mins = 0;
		char colon{};

		istr >> hrs;

		colon = istr.peek();;
		if (colon != ':') {

			istr.setstate(std::ios::failbit);
			return;
		}
		else {
			istr.get();
		}

		istr >> mins;

		if (mins >= 60) {
			hrs += mins / 60;
			mins %= 60;;
		}
		minutes = hrs * 60 + mins;
	}

	Time::operator unsigned int() const
	{
		return minutes;
	}

	Time& Time::operator*=(int val)
	{
		minutes *= val;
		return *this;
	}

	Time& Time::operator-=(const Time& D)
	{
		if (minutes < D.minutes) {
			minutes += 1440;
		}
		minutes -= D.minutes;
		return *this;
	}

	Time Time::operator-(const Time& T) const
	{
		int diff;
		diff = minutes - T.minutes;
		if (diff < 0) {
			diff += 1440;
		}
		return Time(diff);
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& time)
	{
		time.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Time& time) {
		time.read(istr);
		return istr;
	}
}