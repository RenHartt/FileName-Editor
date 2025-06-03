#include "FileRenamerController.hpp"
#include "FileModel.hpp"
#include "MainWindow.hpp"
#include <qcontainerfwd.h>
#include <qfiledialog.h>
#include <qlogging.h>
#include <QMessageBox>
#include <qmessagebox.h>

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
  connect(m_view, &MainWindow::processRequested,
          this, &FileRenamerController::onProcessRequested);
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
  m_view->destEdit()->setText(destDir);
}

void FileRenamerController::onPreviewRequested() {
  QStringList srcs = m_model->srcs();
  QStringList dsts;
  dsts.reserve(srcs.size());
  QString path = m_model->dstFolder();

  if (m_view->mode() == PrefixMode) {
    for (int i = 0; i < srcs.size(); ++i) {
      QFileInfo fi(srcs[i]);
      QString prefix = fi.baseName().isEmpty()
      ? QString{} : QString("%1%2").arg(m_view->prefix()->text()).arg(i) ;
      QString ext = fi.completeSuffix().isEmpty()
      ? QString{} : QString(".%1").arg(fi.completeSuffix());
      dsts << QString("%1/%2%3").arg(path).arg(prefix).arg(ext);
    }
  } else if (m_view->mode() == ReplaceMode) {
    for (int i = 0; i < srcs.size(); ++i) {
      QFileInfo fi(srcs[i]);
      QString fileName = fi.baseName();
      QString ext = fi.completeSuffix().isEmpty()
      ? QString{} : QString(".%1").arg(fi.completeSuffix());
      fileName.replace(m_view->oldEdit()->text(), m_view->newEdit()->text());
      dsts << QString("%1/%2%3").arg(path).arg(fileName).arg(ext);
    }
  }

  m_model->setDsts(dsts);
  m_view->setFileList(srcs, dsts);
}

void FileRenamerController::onProcessRequested() {
  if (m_view->destEdit()->text().isEmpty()) {
    QMessageBox::warning(
      m_view,
      tr("Warning !"),
      tr("Destination folder must be filled.")
    );
    return;
  }
  QStringList srcs = m_model->srcs();
  QStringList dsts = m_model->dsts();
  for(int i = 0; i < srcs.size() && i < dsts.size(); ++i) {
    QFile::copy(srcs[i], dsts[i]);
  }
  QMessageBox::information(
    m_view,
    tr("Succes !"),
    tr("Succes.")
  );
}