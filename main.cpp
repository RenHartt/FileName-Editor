#include <QApplication>
#include <QFile>
#include "FileRenamerController.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile styleFile(":/style.qss");
    if (!styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Impossible de charger :/style.qss";
    } else {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    }

    FileRenamerController controller;
    controller.showMainWindow();

    return app.exec();
}
