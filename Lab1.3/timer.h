//
// Created by Hanh Hoang on 13.1.2025.
//

#ifndef LAB1_TIMER_H
#define LAB1_TIMER_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Time {
    friend std::ostream& operator<<(std::ostream &stream, const Time & time);
    friend std::istream& operator>>(std::istream &stream, Time & time);
public:
    Time operator- (const Time & time);
    Time operator+ (const Time & time);
    bool operator < (const Time &time) const;

private:
    int MINUTES_PER_HOUR = 60;
    int hours, minutes;
};
#endif //LAB1_TIMER_H
