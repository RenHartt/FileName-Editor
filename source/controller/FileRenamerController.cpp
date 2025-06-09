#include "FileRenamerController.hpp"
#include "FileModel.hpp"
#include "MainWindow.hpp"
#include <qcontainerfwd.h>
#include <qfiledialog.h>
#include <qlogging.h>
#include <QMessageBox>
#include <qmessagebox.h>
#include <QFileInfo>

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
  connect(m_view, &MainWindow::cellChanged,
            this, &FileRenamerController::oncellChanged);
}

void FileRenamerController::showMainWindow() {
  m_view->show();
}

void FileRenamerController::oncellChanged(int row, int column) {
  QString newText = m_view->navigationPane()->table()->item(row, column)->text();
  auto files = m_model->files();
  QStringList keys = files.keys();
  if (row < keys.size()) {
      const QString key = keys[row];
      if (column == 0) {
          QString value = files.take(key);
          files.insert(newText, value);
      } else if (column == 1) {
          files[key] = newText;
      }
      m_model->setFiles(files);
  }
}

void FileRenamerController::onBrowseRequested() {
    QStringList paths = QFileDialog::getOpenFileNames(
      m_view,
      tr("Sélectionner des fichiers"),
      QString(),
      tr("Tous fichiers (*)")
    );

    QMap<QString, QString> files;
    for (const QString& p : paths) {
        files.insert(p, QString{});
    }
    m_model->setFiles(files);
    m_view->setFileList(files);
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
  auto files = m_model->files();
  QString path = m_model->dstFolder();

  QStringList keys = files.keys();

  if (m_view->mode() == PrefixMode) {
    for (int i = 0; i < keys.size(); ++i) {
      const QString& src = keys[i];
      QFileInfo fi(src);
      QString prefix = fi.baseName().isEmpty()
      ? QString{} : QString("%1%2").arg(m_view->prefix()->text()).arg(i, QString::number(keys.size()).length(), 10, QChar('0')) ;
      QString ext = fi.completeSuffix().isEmpty()
      ? QString{} : QString(".%1").arg(fi.completeSuffix());
      files[src] = QString("%1/%2%3").arg(path).arg(prefix).arg(ext);
    }
  } else if (m_view->mode() == ReplaceMode) {
    for (int i = 0; i < keys.size(); ++i) {
      const QString& src = keys[i];
      QFileInfo fi(src);
      QString fileName = fi.baseName();
      QString ext = fi.completeSuffix().isEmpty()
      ? QString{} : QString(".%1").arg(fi.completeSuffix());
      fileName.replace(m_view->oldEdit()->text(), m_view->newEdit()->text());
      files[src] = QString("%1/%2%3").arg(path).arg(fileName).arg(ext);
    }
  }

  m_model->setFiles(files);
  m_view->setFileList(files);
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
  auto files = m_model->files();
  for(auto it = files.constBegin(); it != files.constEnd(); ++it) {
    QFile::copy(it.key(), it.value());
  }
  QMessageBox::information(
    m_view,
    tr("Succes !"),
    tr("Succes.")
  );
}