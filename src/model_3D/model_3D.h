#ifndef SRC_MODEL_3D_MODEL_3D
#define SRC_MODEL_3D_MODEL_3D

#include <iostream>
#include <vector>

namespace s21 {
class Model3D {
 public:
  Model3D() {
    matrix_coordinates = std::vector<double>();
    matrix_vertex = std::vector<unsigned int>();
  }

  // Model3D(Model3D& m) {
  //     matrix_coordinates = m.matrix_coordinates;
  //     matrix_vertex = m.matrix_vertex;
  // }

  ~Model3D() {
    matrix_coordinates.clear();
    matrix_vertex.clear();
  }

  std::vector<double>* get_matrix_coordinats() { return &matrix_coordinates; }

  std::vector<unsigned int>* get_matrix_vertex() { return &matrix_vertex; }

  void add_coord(double coord) { matrix_coordinates.push_back(coord); }
  void add_vertex(unsigned int ver) { matrix_vertex.push_back(ver); }

  void copy_model(Model3D& m) {
    matrix_coordinates = m.matrix_coordinates;
    matrix_vertex = m.matrix_vertex;
  }

  void transfer_vector_coordinates(std::vector<double> input_coordinates) {
    for (size_t i = 0; i < matrix_coordinates.size(); i++) {
      matrix_coordinates[i] = 0;
    }
    matrix_coordinates = input_coordinates;
  }

  void clear_model() {
    for (size_t i = 0; i < matrix_coordinates.size(); i++) {
      matrix_coordinates[i] = 0;
    }
    for (size_t i = 0; i < matrix_vertex.size(); i++) {
      matrix_vertex[i] = 0;
    }
    matrix_coordinates.clear();
    matrix_vertex.clear();
  }

 private:
  std::vector<double> matrix_coordinates;
  std::vector<unsigned int> matrix_vertex;
};
}  // namespace s21

#endif