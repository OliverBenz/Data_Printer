#include "Date.hpp"
#include <sstream>
#include <vector>

namespace Printer {
namespace Data {

Date::Date() {
	day = -1;
	month = -1;
	year = -1;
}

Date::Date(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(std::string d) {
	if (d == "") {
		this->day = -1;
		this->month = -1;
		this->year = -1;
	}
	else {
		std::stringstream ss(d);

		std::vector<std::string> vals;
		std::string temp;
		while (getline(ss, temp, '.')) vals.push_back(temp);

		this->day = stoi(vals[0]);
		this->month = stoi(vals[1]);
		this->year = stoi(vals[2]);
	}
}

bool Date::exists(){
	return !(year == -1 || month == -1 || day == -1);
}

// Operators
std::ostream& operator << (std::ostream& os, Date& d) {
	if(! d.exists())
		return (os << "Nan");

	return (os << d.day << "." << d.month << "." << d.year);
}

bool operator == (Date& left, Date& right) {
	return left.year == right.year && left.month == right.month && left.day == right.day;
}

bool operator != (Date& left, Date& right) {
	return !(left == right);
}

bool operator < (Date& left, Date& right) {
	return (left.year < right.year) || (left.year == right.year && left.month < right.month) || (left.year == right.year && left.month == right.month && left.day < right.day);
}

bool operator > (Date& left, Date& right) {
	return !(left == right || left < right);
}

bool operator <= (Date& left, Date& right) {
	return left < right || left == right;
}

bool operator >= (Date& left, Date& right) {
	return left > right || left == right;
}

}
}