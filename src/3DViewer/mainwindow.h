#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>

#include "../controler/controler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString name_file;
  QString filename;
  QString directory;
  // char *name_file;
  void reset_regulator();

 public slots:
  void set_settings_on_form();

 private slots:
  void on_pushButton_file_clicked();
  void on_pushButton_collor_background_clicked();
  void show_color(QColor color, QLabel *label);
  void on_pushButton_collor_edje_clicked();
  void on_pushButton_collor_vertex_clicked();
  void on_comboBox_type_edje_activated(int index);
  void on_horizontalSlider_size_edje_actionTriggered(int action);
  void on_horizontalSlider_size_vertex_actionTriggered(int action);
  void on_comboBox_type_vertex_activated(int index);
  void on_comboBox_projection_activated(int index);

  void on_dial_rotation_X_actionTriggered();
  void on_dial_rotation_Y_actionTriggered();
  void on_dial_rotation_Z_actionTriggered();
  // void on_spinBox_rotation_X_valueChanged();
  // void on_spinBox_rotation_Y_valueChanged();
  // void on_spinBox_rotation_Z_valueChanged();
  void on_dial_rotation_X_sliderMoved(int arg);
  void on_spinBox_rotation_X_valueChanged(int arg);
  void on_dial_rotation_Y_sliderMoved(int arg);
  void on_spinBox_rotation_Y_valueChanged(int arg);
  void on_dial_rotation_Z_sliderMoved(int arg);
  void on_spinBox_rotation_Z_valueChanged(int arg);

  void on_doubleSpinBox_valueChanged(double arg1);  // connect надо добавить

  // screenshot
  void on_pushButton_screenshot_clicked();
  // gif
  void on_pushButton_gif_clicked();

  void create_gif();

  void create_screenshot();

  void on_horizontalSlider_moving_X_actionTriggered();
  void on_horizontalSlider_moving_Y_actionTriggered();
  void on_horizontalSlider_moving_Z_actionTriggered();
  void on_spinBox_horizontal_X_valueChanged(int arg1);
  void on_spinBox_horizontal_Y_valueChanged(int arg1);
  void on_spinBox_horizontal_Z_valueChanged(int arg1);
  void on_horizontalSlider_moving_X_sliderMoved(int position);
  void on_horizontalSlider_moving_Y_sliderMoved(int position);
  void on_horizontalSlider_moving_Z_sliderMoved(int position);

  // void on_dial_rotation_X_sliderMoved(int position);
  void shift();
  void turn();

  // void on_dial_rotation_Y_sliderMoved(int position);

 private:
  double shift_x = 0;
  double shift_y = 0;
  double shift_z = 0;
  double turn_x = 0;
  double turn_y = 0;
  double turn_z = 0;

  Ui::MainWindow *ui;
  QTimer *tmr;  //для скриншота
  int numb;     //для скриншота
};
#endif  // MAINWINDOW_H
