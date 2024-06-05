#include "file_reader.h"

namespace s21 {

int is_digit(char x) {
  int result = 0;
  if (x >= 48 && x <= 57) {
    result = 1;
  }
  return result;
}

bool endsWithObj(std::string path) {
  return path.size() >= 4 && path.compare(path.size() - 4, 4, ".obj") == 0;
}

int FileReader::read_file(Model3D* model, std::string path) {
  int code_error = 0;
  if (endsWithObj(path)) {
    std::ifstream file(path);
    if (file.is_open()) {
      std::string line;
      model->add_coord(0);
      model->add_coord(0);
      model->add_coord(0);
      while (std::getline(file, line)) {
        if (line[0] == 'v' && line[1] == ' ') {
          double x;
          std::stringstream ss(line.substr(2));
          while (ss >> x) {
            model->add_coord(x);
          }
        } else if (line[0] == 'f' && line[1] == ' ') {
          unsigned int last_index = 0;

          std::string line_copy = line;
          char char_arr[1000000] = {0};
          strcpy(char_arr, line_copy.data());
          const char* token = strtok(char_arr + 2, " ");
          last_index = atoi(token);
          model->add_vertex(last_index);
          while (token != NULL) {
            token = strtok(NULL, " ");
            if (token != NULL && is_digit(token[0])) {
              int index = atoi(token);
              model->add_vertex(index);
              model->add_vertex(index);
            }
          }
          model->add_vertex(last_index);
        }
      }

      normalization(model);

      file.close();
    } else {
      code_error = 1;
    }
  } else {
    code_error = 1;
  }

  return code_error;
}

void FileReader::normalization(Model3D* model) {
  // size_t count_coordinats = model->get_matrix_coordinats()->size();
  double max_f = 0;
  size_t count = 0;
  double max_x = *(model->get_matrix_coordinats()->end());
  double max_y = *(model->get_matrix_coordinats()->end());
  double max_z = *(model->get_matrix_coordinats()->end());

  double min_x = *(model->get_matrix_coordinats()->end());
  double min_y = *(model->get_matrix_coordinats()->end());
  double min_z = *(model->get_matrix_coordinats()->end());

  std::vector<double>::iterator it = model->get_matrix_coordinats()->begin();
  while (it != model->get_matrix_coordinats()->end()) {
    if ((*it) > max_x && (count + 6) % 3 == 0) {
      max_x = *it;
    }

    if ((*it) > max_y && (count + 5) % 3 == 0) {
      max_y = *it;
    }

    if ((*it) > max_z && (count + 4) % 3 == 0) {
      max_z = *it;
    }

    if ((*it) < min_x && (count + 6) % 3 == 0) {
      min_x = *it;
    }

    if ((*it) < min_y && (count + 5) % 3 == 0) {
      min_y = *it;
    }

    if ((*it) < min_z && (count + 4) % 3 == 0) {
      min_z = *it;
    }

    ++count;
    ++it;
  }

  double center_x = (max_x + min_x) / 2;
  double center_y = (max_y + min_y) / 2;
  double center_z = (max_z + min_z) / 2;
  count = 0;

  double x = (max_x - min_x) / 2;
  double y = (max_y - min_y) / 2;
  double z = (max_z - min_z) / 2;

  max_f = std::max(std::max(x, y), z);

  it = model->get_matrix_coordinats()->begin();
  while (it != model->get_matrix_coordinats()->end()) {
    if ((count + 6) % 3 == 0) {
      *it -= center_x;
    }

    if ((count + 5) % 3 == 0) {
      *it -= center_y;
    }

    if ((count + 4) % 3 == 0) {
      *it -= center_z;
    }

    if (max_f > 0.8) {
      *it /= (max_f / 10);
    }

    ++count;
    ++it;
  }
}

}  // namespace s21
