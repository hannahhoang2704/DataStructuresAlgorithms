//
// Created by Hanh Hoang on 14.1.2025.
//

#ifndef LAB3_TIME_H
#define LAB3_TIME_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Time {
    friend std::ostream& operator<<(std::ostream &stream, const Time & time);
    friend std::istream& operator>>(std::istream &stream, Time & time);
public:
    explicit Time(int hours=0, int mins=0): hours(hours), minutes(mins) {};
    Time operator- (const Time & time);
    Time operator+ (const Time & time);
    bool operator < (const Time &time) const;
    bool operator ==(const Time &time) const;

private:
    int MINUTES_PER_HOUR = 60;
    int hours, minutes;
};
#endif //LAB3_TIME_H
