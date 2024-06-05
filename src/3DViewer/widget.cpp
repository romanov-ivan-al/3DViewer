#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent) {}

Widget::~Widget() {
  controler.model.m.clear_model();
  controler.model.transf.clear_model();
}

void Widget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  config_params_load();
}

void Widget::paintGL() {
  glClearColor(colorElement.colorBackRed, colorElement.colorBackGreen,
               colorElement.colorBackBlue, 1);  // изменение цвета бэка
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Check_Projection();
  glTranslatef(0.0f, 0.0f, -25.0f);
  drawCube();
  config_params_save();
}

void Widget::resizeGL(int w, int h) {
  w = 25;
  h = 25;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);  // new
  glLoadIdentity();
}

void Widget::drawCube() {
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  glVertexPointer(3, GL_DOUBLE, 0,
                  controler.model.transf.get_matrix_coordinats()->data());
  glEnableClientState(GL_VERTEX_ARRAY);

  // ОТРИСОВКА ТОЧЕК
  glPointSize(sizeVertex);  // размер вершины в пикселях
  glColor3d(colorElement.colorVertexRed,
            colorElement.colorVertexGreen,  //изменение цвета точек
            colorElement.colorVertexBlue);
  if (typeVertex != 2) {
    if (typeVertex == 0) {  // выбор формы отображения вершины
      glEnable(GL_POINT_SMOOTH);  // отображать вершины в форме круга
    } else if (typeVertex == 1) {
      glDisable(GL_POINT_SMOOTH);  //отображать вершины в форме квадрата
    }
    glDrawArrays(GL_POINTS, 1,
                 controler.model.transf.get_matrix_coordinats()->size() / 3);
  }

  // ОТРИСОВКА ЛИНИЙ
  glLineWidth(sizeLine);
  glColor3d(colorElement.colorLineRed, colorElement.colorLineGreen,
            colorElement.colorLineBlue);  // изменение цвета линий
  if (typeLine == 0) {
    glDisable(GL_LINE_STIPPLE);
  }
  if (typeLine == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  }
  glDrawElements(GL_LINES, controler.model.transf.get_matrix_vertex()->size(),
                 GL_UNSIGNED_INT,
                 controler.model.transf.get_matrix_vertex()->data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Widget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void Widget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

int Widget::input_name(QString str) {
  if (str.length() > 0) {
    char *s = str.toUtf8().data();
    for (int i = 0; i < 250; i++) {
      path_to_file[i] = '\0';
    }

    for (size_t i = 0; i < strlen(s); i++) {
      path_to_file[i] = s[i];
    }
  }

  controler.model.m.clear_model();
  controler.model.transf.clear_model();
  code_error = controler.push_name_file(str.toStdString());
  controler.model.transf.copy_model(controler.model.m);
  return code_error;
}

void Widget::Check_Projection() {
  double z_far = 120;
  double shift_m = fabs(mov_x) + fabs(mov_y) + fabs(mov_z);
  if (scale > 1) {
    z_far *= scale;
    shift_m *= scale;
  }
  if (modelProjection == 1) {
    glFrustum(-1, 1, -1, 1, 1, z_far + shift_m);
  } else if (modelProjection == 0) {
    glOrtho(-20, 20, -20, 20, 0.0001, z_far * 2 + shift_m);
  }
}

// Запись в файл настроек
void Widget::config_params_save() {
  QSettings settings("3DViewer_settings.ini", "3D_Viewer");
  settings.beginGroup("Settings");
  settings.setValue("colorElement.colorBackRed", colorElement.colorBackRed);
  settings.setValue("colorElement.colorBackGreen", colorElement.colorBackGreen);
  settings.setValue("colorElement.colorBackBlue", colorElement.colorBackBlue);
  settings.setValue("colorElement.colorVertexRed", colorElement.colorVertexRed);
  settings.setValue("colorElement.colorVertexGreen",
                    colorElement.colorVertexGreen);
  settings.setValue("colorElement.colorVertexBlue",
                    colorElement.colorVertexBlue);
  settings.setValue("colorElement.colorLineRed", colorElement.colorLineRed);
  settings.setValue("colorElement.colorLineGreen", colorElement.colorLineGreen);
  settings.setValue("colorElement.colorLineBlue", colorElement.colorLineBlue);
  settings.setValue("sizeLine", sizeLine);
  settings.setValue("typeLine", typeLine);
  settings.setValue("sizeVertex", sizeVertex);
  settings.setValue("typeVertex", typeVertex);
  settings.setValue("modelProjection", modelProjection);
  settings.endGroup();
}

// Чтение данный из файла
void Widget::config_params_load() {
  QSettings settings("3DViewer_settings.ini", "3D_Viewer");
  settings.beginGroup("Settings");
  colorElement.colorBackRed =
      settings.value("colorElement.colorBackRed", 0).toDouble();
  colorElement.colorBackGreen =
      settings.value("colorElement.colorBackGreen", 0).toDouble();
  colorElement.colorBackBlue =
      settings.value("colorElement.colorBackBlue", 0).toDouble();
  colorElement.colorVertexRed =
      settings.value("colorElement.colorVertexRed", 1).toDouble();
  colorElement.colorVertexGreen =
      settings.value("colorElement.colorVertexGreen", 0).toDouble();
  colorElement.colorVertexBlue =
      settings.value("colorElement.colorVertexBlue", 0).toDouble();
  colorElement.colorLineRed =
      settings.value("colorElement.colorLineRed", 0).toDouble();
  colorElement.colorLineGreen =
      settings.value("colorElement.colorLineGreen", 1).toDouble();
  colorElement.colorLineBlue =
      settings.value("colorElement.colorLineBlue", 0).toDouble();
  sizeLine = settings.value("sizeLine", 1).toInt();
  typeLine = settings.value("typeLine", 1).toInt();
  sizeVertex = settings.value("sizeVertex", 1).toInt();
  typeVertex = settings.value("typeVertex", 1).toInt();
  modelProjection = settings.value("modelProjection", 0).toInt();
  settings.endGroup();
  emit setSettingsOnForm();
}

void Widget::conversion(double shift_x, double shift_y, double shift_z,
                        double turn_x, double turn_y, double turn_z) {
  controler.model.conversion(shift_x, shift_y, shift_z, turn_x, turn_y, turn_z,
                             scale);
  update();
}

void Widget::get_parametrs_model(QString *count_dot, QString *count_poligons) {
  *count_dot =
      QString::number(controler.model.m.get_matrix_coordinats()->size() / 3);
  *count_poligons =
      QString::number(controler.model.m.get_matrix_vertex()->size());
}
