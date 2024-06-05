#include "mainwindow.h"

#include <QAbstractSlider>

#include "qgifimage/qgifimage.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->openGWidget, &Widget::setSettingsOnForm, this,
          &MainWindow::set_settings_on_form);

  tmr = new QTimer();     // создание таймера
  tmr->setInterval(100);  //установка интервала
  connect(
      tmr, SIGNAL(timeout()), this,
      SLOT(create_screenshot()));  // уставновка сигнала на создание скриншота
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_file_clicked() {
  name_file = QFileDialog::getOpenFileName();
  ui->openGWidget->input_name(name_file);
  if (ui->openGWidget->code_error == 0) {
    ui->label->setText(name_file);
  } else {
    ui->label->setText("Error: cannot open file");
  }
  reset_regulator();
  QString count_dot;
  QString count_poligons;
  ui->openGWidget->get_parametrs_model(&count_dot, &count_poligons);
  ui->label_count_dot->setText(count_dot);
  ui->label_count_poligons->setText(count_poligons);
  ui->openGWidget->repaint();
  update();
}

void MainWindow::reset_regulator() {
  ui->horizontalSlider_moving_X->setValue(0);
  ui->horizontalSlider_moving_Y->setValue(0);
  ui->horizontalSlider_moving_Z->setValue(0);

  ui->spinBox_horizontal_X->setValue(0);
  ui->spinBox_horizontal_Y->setValue(0);
  ui->spinBox_horizontal_Z->setValue(0);

  ui->dial_rotation_X->setValue(0);
  ui->dial_rotation_Y->setValue(0);
  ui->dial_rotation_Z->setValue(0);

  ui->spinBox_rotation_X->setValue(0);
  ui->spinBox_rotation_Y->setValue(0);
  ui->spinBox_rotation_Z->setValue(0);

  ui->doubleSpinBox->setValue(1);

  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_pushButton_collor_background_clicked() {
  ui->openGWidget->colorElement.colorBack =
      QColorDialog::getColor(QColor(255, 255, 255, 255));
  if (!ui->openGWidget->colorElement.colorBack.isValid()) {
    qDebug() << "Выбор цвета фона отменён!";
  } else {
    ui->openGWidget->colorElement.colorBackRed =
        ui->openGWidget->colorElement.colorBack.redF();
    ui->openGWidget->colorElement.colorBackGreen =
        ui->openGWidget->colorElement.colorBack.greenF();
    ui->openGWidget->colorElement.colorBackBlue =
        ui->openGWidget->colorElement.colorBack.blueF();
    ui->openGWidget->colorElement.colorBackAlpha =
        ui->openGWidget->colorElement.colorBack.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->openGWidget->colorElement.colorBack,
               ui->label_collor_background);
  }
  ui->openGWidget->repaint();
  update();
}

void MainWindow::show_color(QColor color, QLabel* label) {
  QVariant variant = color;
  QString colorString = variant.toString();
  label->setStyleSheet("QLabel {background-color:" + colorString + ";}");
}

void MainWindow::on_pushButton_collor_edje_clicked() {
  ui->openGWidget->colorElement.colorLine =
      QColorDialog::getColor(QColor(0, 0, 0, 255));
  if (!ui->openGWidget->colorElement.colorLine.isValid()) {
    qDebug() << "Выбор цвета ребер отменён!";
  } else {
    ui->openGWidget->colorElement.colorLineRed =
        ui->openGWidget->colorElement.colorLine.redF();
    ui->openGWidget->colorElement.colorLineGreen =
        ui->openGWidget->colorElement.colorLine.greenF();
    ui->openGWidget->colorElement.colorLineBlue =
        ui->openGWidget->colorElement.colorLine.blueF();
    ui->openGWidget->colorElement.colorLineAlpha =
        ui->openGWidget->colorElement.colorLine.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->openGWidget->colorElement.colorLine, ui->label_collor_edje);
  }
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_pushButton_collor_vertex_clicked() {
  ui->openGWidget->colorElement.colorVertex =
      QColorDialog::getColor(QColor(0, 0, 0, 255));
  if (!ui->openGWidget->colorElement.colorVertex.isValid()) {
    qDebug() << "Выбор цвета точек отменён!";
  } else {
    ui->openGWidget->colorElement.colorVertexRed =
        ui->openGWidget->colorElement.colorVertex.redF();
    ui->openGWidget->colorElement.colorVertexGreen =
        ui->openGWidget->colorElement.colorVertex.greenF();
    ui->openGWidget->colorElement.colorVertexBlue =
        ui->openGWidget->colorElement.colorVertex.blueF();
    ui->openGWidget->colorElement.colorVertexAlpha =
        ui->openGWidget->colorElement.colorVertex.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->openGWidget->colorElement.colorVertex,
               ui->label_collor_vertex);
  }
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_comboBox_type_edje_activated(int index) {
  switch (index) {
    case 0:  // сплошные линии
      ui->openGWidget->typeLine = 0;
      break;
    case 1:  // пунктирные линии
      ui->openGWidget->typeLine = 1;
      break;
  }
  ui->openGWidget->repaint();
  update();
}

// Толщина линий
void MainWindow::on_horizontalSlider_size_edje_actionTriggered(int) {
  ui->openGWidget->sizeLine = ui->horizontalSlider_size_edje->value();
  ui->openGWidget->repaint();
  update();
}

// Толщина точек
void MainWindow::on_horizontalSlider_size_vertex_actionTriggered(int) {
  ui->openGWidget->sizeVertex = ui->horizontalSlider_size_vertex->value();
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_comboBox_type_vertex_activated(int index) {
  switch (index) {
    case 0:  // круг
      ui->openGWidget->typeVertex = 0;
      break;
    case 1:  // квадрат
      ui->openGWidget->typeVertex = 1;
      break;
    case 2:  // отсутствует
      ui->openGWidget->typeVertex = 2;
      break;
  }
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_comboBox_projection_activated(int index) {
  switch (index) {
    case 0:  // Параллельная
      ui->openGWidget->modelProjection = 0;
      break;
    case 1:  // Центральная
      ui->openGWidget->modelProjection = 1;
      break;
    default:
      break;
  }
  ui->openGWidget->repaint();
  update();
}

// Установка значений из конфига на форму
void MainWindow::set_settings_on_form() {
  ui->comboBox_type_edje->setCurrentIndex(ui->openGWidget->typeLine);
  ui->horizontalSlider_size_edje->setValue(ui->openGWidget->sizeLine);
  ui->comboBox_type_vertex->setCurrentIndex(ui->openGWidget->typeVertex);
  ui->horizontalSlider_size_vertex->setValue(ui->openGWidget->sizeVertex);
  ui->comboBox_projection->setCurrentIndex(ui->openGWidget->modelProjection);

  // Конвертация закружаемых значений RGB в QColor
  ui->openGWidget->colorElement.colorBack =
      ui->openGWidget->colorElement.colorBack.fromRgbF(
          ui->openGWidget->colorElement.colorBackRed,
          ui->openGWidget->colorElement.colorBackGreen,
          ui->openGWidget->colorElement.colorBackBlue, 1);
  ui->openGWidget->colorElement.colorVertex =
      ui->openGWidget->colorElement.colorVertex.fromRgbF(
          ui->openGWidget->colorElement.colorVertexRed,
          ui->openGWidget->colorElement.colorVertexGreen,
          ui->openGWidget->colorElement.colorVertexBlue, 1);
  ui->openGWidget->colorElement.colorLine =
      ui->openGWidget->colorElement.colorLine.fromRgbF(
          ui->openGWidget->colorElement.colorLineRed,
          ui->openGWidget->colorElement.colorLineGreen,
          ui->openGWidget->colorElement.colorLineBlue, 1);

  show_color(ui->openGWidget->colorElement.colorBack,
             ui->label_collor_background);
  show_color(ui->openGWidget->colorElement.colorVertex,
             ui->label_collor_vertex);
  show_color(ui->openGWidget->colorElement.colorLine, ui->label_collor_edje);
  ui->openGWidget->repaint();
  update();
}

//--------------screenshot---------------------
void MainWindow::on_pushButton_screenshot_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      0, "Open Dialog", "",
      tr("Images (*.jpeg *.bmp )"));  // сохранение файла и изменение расширения
  if (filename != "")
    ui->openGWidget->grab().save(filename);  // захват виджета и сохранение
}
//--------------screenshot---------------------

//--------------gif---------------------
void MainWindow::on_pushButton_gif_clicked() {
  filename = QFileDialog::getSaveFileName(
      0, "Open Dialog", "",
      tr("Images (*.gif )"));  // сохранение файла и изменение расширенияы
  //    QString tempfilename = filename;
  directory =
      QFileInfo(filename).absoluteDir().absolutePath() + "/screenshot_gif/";
  tmr->start();  // запуск таймера
  QDir dir(directory);  //проверка и создание папки если её нет
  if (!dir.exists()) {
    dir.mkpath(".");  // создание папки если её нет
  }
  numb = 0;
  create_screenshot();
}

void MainWindow::create_screenshot() {
  if (numb < 50) {  // пока не созданны все кадры
    ui->openGWidget->grab().scaled(640, 480).save(
        directory + QString::number(numb) +
        ".png");  // захват виджета и сохранение
    numb++;       // добавление 1 к имени файла
  }

  if (numb == 49) {  // как только все 49 кадров созданны можно создавать gif
    create_gif();
  }
}

void MainWindow::create_gif() {    // создание gif
  QDir dir_screenshot(directory);  //папка с скриншотами
  QString name = "";               // имя фотки
  QGifImage gif(QSize(640, 480));  // определение размера
  gif.setDefaultDelay(10);  // задержка анимации между картинками 0.1 секунда
  QImage image(640, 480, QImage::Format_RGB32);  // обьявление изображения
  for (int i = 0; i < numb;
       i++) {  // проходиться по изображениям и создавать из них gif
    name = directory + "/" + QString::number(i) +
           ".png";  //проходимся по каждой фотке
    image.load(name, "PNG");  // загрузка
    gif.addFrame(image);      //добавление в гиф формат
  }
  if (filename != "") gif.save(filename);  //сохранение гифки
  dir_screenshot.removeRecursively();  // удаление папки с скриншотами

  tmr->stop();  // останавливаем таймер скриншотов
  numb = 0;  // обнуляем переменную после окончания
  directory = "";
  filename = "";
}
//--------------gif---------------------

// Перемещения
void MainWindow::on_horizontalSlider_moving_X_actionTriggered() {
  ui->openGWidget->mov_x = ui->horizontalSlider_moving_X->value();
  ui->spinBox_horizontal_X->setValue(ui->horizontalSlider_moving_X->value());
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_horizontalSlider_moving_Y_actionTriggered() {
  ui->openGWidget->mov_y = ui->horizontalSlider_moving_Y->value();
  ui->spinBox_horizontal_Y->setValue(ui->horizontalSlider_moving_Y->value());
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_horizontalSlider_moving_Z_actionTriggered() {
  ui->openGWidget->mov_z = ui->horizontalSlider_moving_Z->value();
  ui->spinBox_horizontal_Z->setValue(ui->horizontalSlider_moving_Z->value());
  ui->openGWidget->repaint();
  update();
}

void MainWindow::on_spinBox_horizontal_X_valueChanged(int arg1) {
  on_horizontalSlider_moving_X_sliderMoved(arg1);
  ui->horizontalSlider_moving_X->setValue(arg1);
  update();
}

void MainWindow::on_spinBox_horizontal_Y_valueChanged(int arg1) {
  on_horizontalSlider_moving_Y_sliderMoved(arg1);
  ui->horizontalSlider_moving_Y->setValue(arg1);
  update();
}

void MainWindow::on_spinBox_horizontal_Z_valueChanged(int arg1) {
  on_horizontalSlider_moving_Z_sliderMoved(arg1);
  ui->horizontalSlider_moving_Z->setValue(arg1);
  update();
}

void MainWindow::on_horizontalSlider_moving_X_sliderMoved(int position) {
  shift_x = position;
  shift();
  update();
}

void MainWindow::on_horizontalSlider_moving_Y_sliderMoved(int position) {
  shift_y = position;
  shift();
  update();
}

void MainWindow::on_horizontalSlider_moving_Z_sliderMoved(int position) {
  shift_z = position;
  shift();
  update();
}

void MainWindow::shift() {
  ui->openGWidget->conversion(shift_x, shift_y, shift_z, turn_x, turn_y,
                              turn_z);
  update();
}

// Повороты
void MainWindow::on_dial_rotation_X_sliderMoved(int arg) {
  turn_x = arg;
  turn();
}

void MainWindow::on_spinBox_rotation_X_valueChanged(int arg) {
  on_dial_rotation_X_sliderMoved(arg);
  ui->dial_rotation_X->setValue(arg);
}

void MainWindow::on_dial_rotation_Y_sliderMoved(int arg) {
  turn_y = arg;
  turn();
}

void MainWindow::on_spinBox_rotation_Y_valueChanged(int arg) {
  on_dial_rotation_Y_sliderMoved(arg);
  ui->dial_rotation_Y->setValue(arg);
}

void MainWindow::on_dial_rotation_Z_sliderMoved(int arg) {
  turn_z = arg;
  turn();
}

void MainWindow::on_spinBox_rotation_Z_valueChanged(int arg) {
  on_dial_rotation_Z_sliderMoved(arg);
  ui->dial_rotation_Z->setValue(arg);
}

void MainWindow::turn() {
  ui->openGWidget->conversion(shift_x, shift_y, shift_z, turn_x, turn_y,
                              turn_z);
}

void MainWindow::on_dial_rotation_X_actionTriggered() {
  ui->spinBox_rotation_X->setValue(ui->dial_rotation_X->value());
}

void MainWindow::on_dial_rotation_Y_actionTriggered() {
  ui->spinBox_rotation_Y->setValue(ui->dial_rotation_Y->value());
}

void MainWindow::on_dial_rotation_Z_actionTriggered() {
  ui->spinBox_rotation_Z->setValue(ui->dial_rotation_Z->value());
}

//  Масштабирование
void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  ui->openGWidget->scale = arg1;
  ui->openGWidget->conversion(shift_x, shift_y, shift_z, turn_x, turn_y,
                              turn_z);
  ui->openGWidget->repaint();
  update();
}
