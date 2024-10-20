#include <iostream>
#include <string>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    bool isLeapYear(int year) const {
        return (year % 4 == 0);
    }

    int daysInMonth(int month, int year) const {
        int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return daysPerMonth[month - 1];
    }

public:
    Date() : year(2000), month(1), day(1) {}

    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    void addDay() {
        day++;
        if (day > daysInMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    void subDay() {
        day--;
        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = daysInMonth(month, year);
        }
    }


    Date operator++(int) {
        addDay();
        return *this;
    }

    Date operator--(int) {
        subDay();
        return *this;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator>(const Date& other) const {
        if (year != other.year) {
            return year > other.year;
        }
        if (month != other.month) {
            return month > other.month;
        }
        return day > other.day;
    }

    bool operator<(const Date& other) const {
        return other > *this;
    }

    friend ostream& operator<<(ostream& out, const Date& date) {
        out << date.year << '.' << date.month << '.' << date.day;
        return out;
    }

    friend istream& operator>>(istream& in, Date& date) {
        char symbol = '.';
        in >> date.year >> symbol >> date.month >> symbol >> date.day;
        return in;
    }

    Date& operator=(const Date& other) {
        year = other.year;
        month = other.month;
        day = other.day;
        return *this;
    }

    Date& operator+=(int days) {
        for (int i = 0; i < days; i++) {
            addDay();
        }
        return *this;
    }

    Date& operator-=(int days) {
        for (int i = 0; i < days; i++) {
            subDay();
        }
        return *this;
    }

    int operator()(const string& type) const {
        if (type == "day") {
            return day;
        }
        else if (type == "month") {
            return month;
        }
        else if (type == "year") {
            return year;
        }
        return -1;
    }
};

int main() {
    Date d;
    Date d1(2008, 10, 1);
    d++;
    cout << d << endl;
    d -= 2;
    cout << d << endl;
    cout << "Day: " << d("day") << endl;

    /*cin >> d;
    cout << d;
    d = d1;
    cout << d;*/
}
