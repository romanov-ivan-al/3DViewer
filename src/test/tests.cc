#include <gtest/gtest.h>

#include "../conversionModel/conversionModel.h"
#include "../file_reader/file_reader.h"

TEST(OpenFile, OpenTrue) {
  s21::FileReader reader;
  s21::Model3D model;
  int code_error = reader.read_file(&model, "./test/cube.obj");
  EXPECT_EQ(code_error, 0);
}

TEST(OpenFile, OpenFalse) {
  s21::FileReader reader;
  s21::Model3D model;
  int code_error = reader.read_file(&model, "./test/grut");
  EXPECT_EQ(code_error, 1);
}

TEST(OpenFile, CheckCoordinatsPoligons) {
  s21::FileReader reader;
  s21::Model3D model;
  reader.read_file(&model, "./test/cube.obj");

  std::vector<double> coordinats = {-10, -10, -10, -10, -10, -10, -10, -10, 10,
                                    -10, 10,  -10, -10, 10,  10,  10,  -10, -10,
                                    10,  -10, 10,  10,  10,  -10, 10,  10,  10};

  std::vector<unsigned int> poligons = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2,
      2, 4, 4, 1, 3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8,
      8, 5, 5, 8, 8, 6, 6, 5, 1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1};

  for (size_t i = 0; i < model.get_matrix_coordinats()->size(); i++) {
    EXPECT_EQ(coordinats.data()[i], model.get_matrix_coordinats()->data()[i]);
  }

  for (size_t i = 0; i < model.get_matrix_vertex()->size(); i++) {
    EXPECT_EQ(poligons.data()[i], model.get_matrix_vertex()->data()[i]);
  }
}

TEST(OpenFile, CheckTurn) {
  s21::FileReader reader;
  s21::Model3D model;
  s21::conversionModel conversion_m;
  std::vector<double> tmp;
  reader.read_file(&model, "./test/cube.obj");

  std::vector<double> values = {
      -10, -8.88178e-16, -14.1421,    -10, -8.88178e-16, -14.1421,
      -10, -14.1421,     8.88178e-16, -10, 14.1421,      -8.88178e-16,
      -10, 8.88178e-16,  14.1421,     10,  -8.88178e-16, -14.1421,
      10,  -14.1421,     8.88178e-16, 10,  14.1421,      -8.88178e-16,
      10,  8.88178e-16,  14.1421};
  for (std::vector<double>::size_type i = 0;
       i < model.get_matrix_coordinats()->size(); i++) {
    tmp.push_back(model.get_matrix_coordinats()->at(i));
  }
  conversion_m.turn(*model.get_matrix_coordinats(), tmp, 45, 0, 0);

  for (size_t i = 0; i < model.get_matrix_coordinats()->size(); i++) {
    EXPECT_NEAR(values.data()[i], model.get_matrix_coordinats()->data()[i],
                0.001);
  }
}

TEST(OpenFile, CheckShift) {
  s21::FileReader reader;
  s21::Model3D model;
  s21::conversionModel conversion_m;
  std::vector<double> tmp;
  reader.read_file(&model, "./test/cube.obj");

  std::vector<double> values = {
      -7.33333, -10, -10, -7.33333, -10, -10, -7.33333, -10, 10,
      -7.33333, 10,  -10, -7.33333, 10,  10,  12.6667,  -10, -10,
      12.6667,  -10, 10,  12.6667,  10,  -10, 12.6667,  10,  10};
  for (std::vector<double>::size_type i = 0;
       i < model.get_matrix_coordinats()->size(); i++) {
    tmp.push_back(model.get_matrix_coordinats()->at(i));
  }
  conversion_m.shift(*model.get_matrix_coordinats(), tmp, 40, 0, 0);

  for (size_t i = 0; i < model.get_matrix_coordinats()->size(); i++) {
    EXPECT_NEAR(values.data()[i], model.get_matrix_coordinats()->data()[i],
                0.001);
  }
}

TEST(OpenFile, CheckScale) {
  s21::FileReader reader;
  s21::Model3D model;
  s21::conversionModel conversion_m;
  std::vector<double> tmp;
  reader.read_file(&model, "./test/cube.obj");

  std::vector<double> values = {-30, -30, -30, -30, -30, -30, -30, -30, 30,
                                -30, 30,  -30, -30, 30,  30,  30,  -30, -30,
                                30,  -30, 30,  30,  30,  -30, 30,  30,  30};
  for (std::vector<double>::size_type i = 0;
       i < model.get_matrix_coordinats()->size(); i++) {
    tmp.push_back(model.get_matrix_coordinats()->at(i));
  }
  conversion_m.scale(*model.get_matrix_coordinats(), tmp, 3);

  for (size_t i = 0; i < model.get_matrix_coordinats()->size(); i++) {
    EXPECT_NEAR(values.data()[i], model.get_matrix_coordinats()->data()[i],
                0.001);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
