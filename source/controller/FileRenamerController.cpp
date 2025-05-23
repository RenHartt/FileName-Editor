#include "include/FileRenamerController.hpp"

FileRenamerController::FileRenamerController(FileModel* model, QObject* parent) : QObject(parent), m_model(model) {
    connect(m_model, &FileModel::fileListChanged, this, &FileRenamerController::fileListChanged);
}

void FileRenamerController::addFile(const QString& path, bool selected) {
    m_model->addFile(path, selected);
}

void FileRenamerController::removeFile(const QString& path) {
    m_model->removeFile(path);
}

void FileRenamerController::selectFile(const QString& path) {
    m_model->selectFile(path);
}

void FileRenamerController::deselectFile(const QString& path) {
    m_model->deselectFile(path);
}

void FileRenamerController::renameSelected(const QString& prefix) {
    m_model->renameFiles(prefix);
}

void FileRenamerController::replaceSelected(const QString& oldText, const QString& newText) {
    m_model->replaceInFilesName(oldText, newText);
}
