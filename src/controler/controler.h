#ifndef CONTROLER_H
#define CONTROLER_H

// #include "../model/model.h"
#include "../Viewer3DManager/Viewer3DManager.h"

namespace s21 {

class Controler {
  //  private:
 public:
  s21::Viewer3DManager model;

  //  public:
  Controler() = default;
  ~Controler() = default;

  int push_name_file(std::string path_to_file) {
    return model.push_model(path_to_file);
  }
};

}  // namespace s21

#endif  // CONTROLER_H
