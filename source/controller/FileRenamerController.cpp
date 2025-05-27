#include "FileRenamerController.hpp"
#include "FileModel.hpp"
#include "MainWindow.hpp"

FileRenamerController::FileRenamerController(QObject* parent)
  : QObject(parent),
  m_view(new MainWindow),
  m_model(new FileModel) {

    connect(m_view->filePanel(), &FileSelectionPanel::browseRequested, this, &FileRenamerController::onBrowseRequested);
    connect(this, &FileRenamerController::filesUpdated, m_view, &MainWindow::setFileList);
  }

void FileRenamerController::showMainWindow() {
  m_view->show();
}

void FileRenamerController::onBrowseRequested()
{
    QStringList files = QFileDialog::getOpenFileNames(
      m_view,
      tr("Sélectionner des fichiers"),
      QString(),
      tr("Tous fichiers (*)")
    );

    for (const QString& f : files) {
        m_model->addFile(f, true);
    }

    emit filesUpdated(m_model->getFiles().keys());
}