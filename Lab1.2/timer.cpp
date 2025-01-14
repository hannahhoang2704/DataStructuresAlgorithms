//
// Created by Hanh Hoang on 13.1.2025.
//
#include "timer.h"

std::ostream &operator<<(std::ostream &stream, const Time &time) {
  stream << std::setfill('0') << std::setw(2) << time.hours;
  std::cout << ":" << std::setfill('0') << std::setw(2) << time.minutes
            << std::endl;
  return stream;
}

std::istream &operator>>(std::istream &stream, Time &time) {
  stream >> time.hours;
  stream >> time.minutes;
  return stream;
}

Time Time::operator-(const Time &time) {
  Time duration;
  int timeDifference = hours * MINUTES_IN_HOUR + minutes -
                       (time.hours * MINUTES_IN_HOUR + time.minutes);
  duration.hours = timeDifference / MINUTES_IN_HOUR;
  duration.minutes = timeDifference % MINUTES_IN_HOUR;
  return duration;
}

Time Time::operator+(const Time &time) {
  Time endTime;
  int totalTime =
      (hours + time.hours) * MINUTES_IN_HOUR + minutes + time.minutes;
  endTime.hours = totalTime / MINUTES_IN_HOUR;
  endTime.minutes = totalTime % MINUTES_IN_HOUR;
  return endTime;
}

bool Time::operator<(const Time &time) {
  if (hours == time.hours) {
    return minutes < time.minutes;
  };
  return hours < time.hours;
}
