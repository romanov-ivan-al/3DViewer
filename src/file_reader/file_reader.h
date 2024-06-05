#ifndef SRC_FILE_READER_FILE_READER
#define SRC_FILE_READER_FILE_READER

#include <math.h>
#include <string.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#include "../model_3D/model_3D.h"
namespace s21 {
class FileReader {
 public:
  int read_file(Model3D* model, std::string path);

 private:
  void normalization(Model3D* model);
};
}  // namespace s21

#endif