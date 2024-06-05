#ifndef CONVERSIONMODEL_H
#define CONVERSIONMODEL_H
#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {
class conversionModel {
 public:
  void shift(std::vector<double>& data_shift, std::vector<double>& data,
             double x, double y, double z);
  void turn(std::vector<double>& data_turn, std::vector<double>& data, double x,
            double y, double z);
  void scale(std::vector<double>& data_shift, std::vector<double>& data,
             double x);

 private:
};
}  // namespace s21

#endif  // CONVERSIONMODEL_H
