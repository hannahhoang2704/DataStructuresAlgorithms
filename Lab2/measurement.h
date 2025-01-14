//
// Created by Hanh Hoang on 14.1.2025.
//

#ifndef LAB2_MEASUREMENT_H
#define LAB2_MEASUREMENT_H
#include <fstream>
#include <iostream>
#include <sstream>

class Measurements {
 public:
  Measurements();
  ~Measurements();
  Measurements &operator=(const Measurements &other);
  bool read(const char *filename);
  void print() const;
  double mean();
  void inc(double increment);

 private:
  double *value_stores;
  int count;
};
#endif  // LAB2_MEASUREMENT_H
