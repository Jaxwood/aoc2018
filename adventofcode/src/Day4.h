#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace Day4 {

	class Record {
	private:
		int _year;
		int _month;
		int _day;
		int _hour;
		int _minute;
		std::string _instruction;
	public:
		Record(int year, int month, int day, int hour, int minute, std::string instruction)
		{
			this->_year = year;
			this->_month = month;
			this->_day = day;
			this->_hour = hour;
			this->_minute = minute;
			_instruction = instruction;
		}

		bool operator<(const Record r2) {
			if (this->_year != r2._year) {
				return this->_year < r2._year;
			}
			if (this->_month != r2._month) {
				return this->_month < r2._month;
			}
			if (this->_day != r2._day) {
				return this->_day < r2._day;
			}
			if (this->_hour != r2._hour) {
				return this->_hour < r2._hour;
			}
			if (this->_minute != r2._minute) {
				return this->_minute < r2._minute;
			}
			return false;
		}

	};

	int Part1(std::vector<Record> tokens);
}
