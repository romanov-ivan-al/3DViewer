#include "conversionModel.h"

namespace s21 {

void conversionModel::shift(std::vector<double>& data_shift,
                            std::vector<double>& data, double x, double y,
                            double z) {
  if (data.size() % 3 > 0) {
    // std::cout << "\nERROR\n";
    throw std::invalid_argument("incorrect number of coordinates");
  }
  for (std::vector<double>::size_type i = 0; i < data.size(); i += 3) {
    data_shift[i] = data[i] + x / 15;
    data_shift[i + 1] = data[i + 1] + y / 15;
    data_shift[i + 2] = data[i + 2] + z / 15;
  }
}

void conversionModel::scale(std::vector<double>& data_shift,
                            std::vector<double>& data, double x) {
  for (std::vector<double>::size_type i = 0; i < data.size(); i++) {
    data[i] *= x;
    data_shift[i] = data[i];
  }
}

void conversionModel::turn(std::vector<double>& data_turn,
                           std::vector<double>& data, double x, double y,
                           double z) {
  double x0 = 0, y0 = 0, z0 = 0;
  x *= M_PI / 180;  // перевод градусов в радианы
  y *= M_PI / 180;  // перевод градусов в радианы
  z *= M_PI / 180;  // перевод градусов в радианы
  // Поворот по оси X
  for (std::vector<double>::size_type i = 0; i < data.size() / 3; i++) {
    y0 = data[i * 3 + 1];
    z0 = data[i * 3 + 2];
    data[i * 3 + 1] = cos(x) * y0 - sin(x) * z0;
    data[i * 3 + 2] = sin(x) * y0 + cos(x) * z0;
  }
  // Поворот по оси Y
  for (std::vector<double>::size_type i = 0; i < data.size() / 3; i++) {
    x0 = data[i * 3];
    z0 = data[i * 3 + 2];
    data[i * 3] = cos(y) * x0 + sin(y) * z0;
    data[i * 3 + 2] = cos(y) * z0 - sin(y) * x0;
  }
  // Поворот по оси Z
  for (std::vector<double>::size_type i = 0; i < data.size() / 3; i++) {
    x0 = data[i * 3];
    y0 = data[i * 3 + 1];
    data[i * 3] = cos(z) * x0 - sin(z) * y0;
    data[i * 3 + 1] = sin(z) * x0 + cos(z) * y0;
  }
  for (std::vector<double>::size_type i = 0; i < data_turn.size(); i++) {
    data_turn[i] = data[i];
  }
}
}  // namespace s21
