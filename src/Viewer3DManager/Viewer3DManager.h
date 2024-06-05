#ifndef SRC_VIEWER_3D_MANAGER
#define SRC_VIEWER_3D_MANAGER

#include "../conversionModel/conversionModel.h"
#include "../file_reader/file_reader.h"
#include "../model_3D/model_3D.h"

namespace s21 {
class Viewer3DManager {
 public:
  Model3D m;
  Model3D transf;
  conversionModel conversion_m;

  int push_model(std::string path_to_file) {
    return reader.read_file(&m, path_to_file);
  }

  void conversion(double shift_x, double shift_y, double shift_z, double turn_x,
                  double turn_y, double turn_z, double scale) {
    std::vector<double> tmp;
    for (std::vector<double>::size_type i = 0;
         i < m.get_matrix_coordinats()->size(); i++) {
      tmp.push_back(m.get_matrix_coordinats()->at(i));
    }

    conversion_m.turn(*transf.get_matrix_coordinats(), tmp, turn_x, turn_y,
                      turn_z);
    conversion_m.scale(*transf.get_matrix_coordinats(), tmp, scale);
    conversion_m.shift(*transf.get_matrix_coordinats(), tmp, shift_x, shift_y,
                       shift_z);
  }

 private:
  FileReader reader;
};
}  // namespace s21

#endif
