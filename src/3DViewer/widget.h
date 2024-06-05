#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPoint>
#include <QSettings>
#include <QTimer>
#include <QtWidgets/QWidget>

#include "../controler/controler.h"
#include "mainwindow.h"

typedef struct colorStruct {
  QColor colorVertex;
  QColor colorLine;
  QColor colorBack;

  double colorVertexRed;
  double colorVertexGreen;
  double colorVertexBlue;
  double colorVertexAlpha = 255;

  double colorLineRed;
  double colorLineGreen;
  double colorLineBlue;
  double colorLineAlpha = 255;

  double colorBackRed;
  double colorBackGreen;
  double colorBackBlue;
  double colorBackAlpha = 255;
} colorData;

class Widget : public QOpenGLWidget {
  Q_OBJECT
 public:
  // Атрибуты линий и вершин
  int sizeLine;
  int typeLine;
  int sizeVertex;
  int typeVertex;
  colorData colorElement;

  //   // масштаб
  //    double scaleModel;

  // проекция
  int modelProjection;
  int code_error = 0;

  explicit Widget(QWidget* parent = nullptr);
  ~Widget();
  //  obj_3D model;
  //  obj_3D model_copy;
  s21::Controler controler;

  void conversion(double shift_x, double shift_y, double shift_z, double turn_x,
                  double turn_y, double turn_z);

  std::string path;
  char path_to_file[250];
  int input_name(QString str);
  void get_parametrs_model(QString* count_dot, QString* count_poligons);
  // перемещение и вращение
  double mov_x, mov_y, mov_z, scale = 1;
  float xRot, yRot, zRot;

  //  protected:

 private:
  QPoint mPos;
  QTimer tmr;
  void drawCube();
  void mousePressEvent(QMouseEvent* mo) override;
  void mouseMoveEvent(QMouseEvent* mo) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void Check_Projection();
  void config_params_save();
  void config_params_load();
  void model_centering();
 signals:
  void setSettingsOnForm();
};

#endif  // WIDGET_H
