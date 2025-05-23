TEMPLATE = app
TARGET = FileRenamer
INCLUDEPATH += include

QT += widgets

# Input
HEADERS += include/FileModel.hpp \
           include/FileRenamerController.hpp \
           include/MainWindow.hpp
SOURCES += main.cpp \
           source/controller/FileRenamerController.cpp \
           source/model/FileModel.cpp \
           source/view/MainWindow.cpp
