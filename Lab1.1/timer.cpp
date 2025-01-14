//
// Created by Hanh Hoang on 13.1.2025.
//
#include "timer.h"


void Time::read(const std::string &prompt) {
    std::cout << prompt << " (hh:mm): " << std::endl;
    std::string input;
    std::cin >> input;

    char delimiter = ':';
    std::istringstream stream(input);
    if (!(stream >> hours >> delimiter >> minutes) || hours < 0 || hours > 23 || minutes < 0 || minutes > 59){
        std::cout << "Invalid input. Retry: " << std::endl;
        read(prompt);
    }
}

bool Time::lessThan(const Time &t) const {
    if (hours  == t.hours){
        return minutes < t.minutes;
    };
    return hours < t.hours;
}

Time Time::subtract(const Time &t) const {
    Time duration;
    int totalInMinutes = hours * 60 + minutes;
    int timeDifference = totalInMinutes - (t.hours * 60 + t.minutes);
    if (timeDifference < 60){
        duration.hours = 0;
        duration.minutes = timeDifference;
    } else {
        duration.hours = timeDifference / 60;
        duration.minutes = timeDifference % 60;
    }
    return duration;
}

void Time::display() const {
    std::cout << std::setiosflags(std::ios::right);
    std::cout << std::setfill('0') << std::setw(2) << hours; std::cout << ":" << std::setfill('0') << std::setw(2) << minutes << std::endl;
}
