#include "FileRenamerController.hpp"
#include "FileModel.hpp"
#include "MainWindow.hpp"
#include <qcontainerfwd.h>
#include <qfiledialog.h>
#include <qlogging.h>

FileRenamerController::FileRenamerController(QObject* parent)
  : QObject(parent),
  m_view(new MainWindow),
  m_model(new FileModel) {

  connect(m_view, &MainWindow::browseRequested,
         this, &FileRenamerController::onBrowseRequested);
  connect(m_view, &MainWindow::previewRequested,
           this, &FileRenamerController::onPreviewRequested);
  connect(m_view, &MainWindow::destRequested,
          this, &FileRenamerController::onDestRequested);
}

void FileRenamerController::showMainWindow() {
  m_view->show();
}

void FileRenamerController::onBrowseRequested() {
    QStringList files = QFileDialog::getOpenFileNames(
      m_view,
      tr("Sélectionner des fichiers"),
      QString(),
      tr("Tous fichiers (*)")
    );

    m_model->setSrcs(files);
    m_view->setFileList(files, QStringList{});
}

void FileRenamerController::onDestRequested() {
  QString destDir = QFileDialog::getExistingDirectory(
    m_view, 
    tr("Select A folder"),
    QDir::homePath(),
    QFileDialog::ShowDirsOnly
  );

  m_model->setDstFolder(destDir);
  m_view->destEdit()->setPlaceholderText(destDir);
}

void FileRenamerController::onPreviewRequested() {
  QStringList srcs = m_model->srcs();
  QStringList dsts;
  dsts.reserve(srcs.size());
  
  QString path = m_model->dstFolder();
  if (m_view->mode() == PrefixMode) {
    QString prefix = m_view->prefix()->text();
    for (int i = 0; i < srcs.size(); ++i) {
      QFileInfo fi(srcs[i]);
      QString ext = fi.suffix().isEmpty() 
      ? QString{}
      : QString(".%1").arg(fi.suffix());
      dsts << QString("%1/%2%3%4").arg(path).arg(prefix).arg(i).arg(ext);
    }
  } else if (m_view->mode() == ReplaceMode) {
    for (int i = 0; i < srcs.size(); ++i) {
      QFileInfo fi(srcs[i]);
      QString fileName = fi.fileName();
      QString ext = fi.suffix().isEmpty()
      ? QString{}
      : QString(".%1").arg(fi.suffix());
      fileName.replace(m_view->oldEdit()->text(), m_view->newEdit()->text());
      dsts << QString("%1/%2%3").arg(path).arg(fileName).arg(ext);
    }
  }
  m_model->setDsts(dsts);
  m_view->setFileList(srcs, dsts);
}

void FileRenamerController::onProcessRequested() {
  
}