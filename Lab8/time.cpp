//
// Created by Hanh Hoang on 14.1.2025.
//

#include "time.h"

std::ostream& operator<<(std::ostream &stream, const Time & time){
    stream << std::setfill('0') << std::setw(2) << time.hours; std::cout << ":" << std::setfill('0') << std::setw(2) << time.minutes;
    return stream;
}

std::istream& operator>>(std::istream &stream, Time & time){
    stream >> time.hours;
    stream >> time.minutes;
    return stream;
}

Time Time::operator- (const Time &time) {
    Time duration;
    int timeDifference = hours * MINUTES_PER_HOUR + minutes - (time.hours * MINUTES_PER_HOUR + time.minutes);
    duration.hours = timeDifference / MINUTES_PER_HOUR;
    duration.minutes = timeDifference % MINUTES_PER_HOUR;
    return duration;
}

Time Time::operator+ (const Time &time){
    Time end;
    int totalTime = (hours + time.hours)*MINUTES_PER_HOUR + minutes + time.minutes;
    end.hours = totalTime / MINUTES_PER_HOUR;
    end.minutes = totalTime % MINUTES_PER_HOUR;
    return end;
}

bool Time::operator< (const Time &time) const {
    if (hours  == time.hours){
        return minutes < time.minutes;
    };
    return hours < time.hours;
}

bool Time::operator==(const Time &time) const{
    return hours == time.hours && minutes == time.minutes;
}