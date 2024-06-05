QT       += core gui openglwidgets opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    widget.cpp \
    qgifimage/dgif_lib.c \
    qgifimage/egif_lib.c \
    qgifimage/gif_err.c \
    qgifimage/gif_font.c \
    qgifimage/gif_hash.c \
    qgifimage/gifalloc.c \
    qgifimage/qgifimage.cpp \
    qgifimage/quantize.c \
    ../controler/controler.cc \
    ../file_reader/file_reader.cc \
    ../conversionModel/conversionModel.cc


HEADERS += \
    mainwindow.h \
    widget.h \
    qgifimage/gif_hash.h \
    qgifimage/gif_lib.h \
    qgifimage/gif_lib_private.h \
    qgifimage/qgifglobal.h \
    qgifimage/qgifimage.h \
    qgifimage/qgifimage_p.h \
    ../controler/controler.h \
    ../model_3D/model_3D.h \
    ../file_reader/file_reader.h \
    ../Viewer3DManager/Viewer3DManager.h \
    ../conversionModel/conversionModel.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
