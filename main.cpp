#include <QCoreApplication>
#include "include/FileRenamerController.hpp"
#include "qcoreapplication.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    FileModel fileModel;
    FileRenamerController controller(&fileModel);
    
    controller.addFile("/home/bgoron/Qt-shit/FileRenamer/test.txt");
    std::cout << fileModel << std::endl;
    controller.selectFile("/home/bgoron/Qt-shit/FileRenamer/test.txt");
    controller.renameSelected("ouiiii");
    std::cout << fileModel << std::endl;

    return 0;
}
