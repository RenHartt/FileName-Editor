#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <qcontainerfwd.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <QFileDialog>

class NavigationPane : public QWidget {
    Q_OBJECT
public:
    explicit NavigationPane(QWidget* parent = nullptr);

public slots:
    void setFiles(const QStringList& list);

private:
    QVBoxLayout* m_layout;
    QListWidget* m_fileList;
};

class FileSelectionPanel : public QWidget {
    Q_OBJECT
public:
    explicit FileSelectionPanel(QWidget* parent = nullptr);

signals:
    void browseRequested();

private:
    QHBoxLayout* m_buttonLayout;
    QPushButton* m_browse;
    QPushButton* m_selectAll;
    QPushButton* m_deselectAll;
};

class ReplaceOptionsPanel : public QWidget {
    Q_OBJECT
public:
  explicit ReplaceOptionsPanel(QWidget* parent = nullptr);

signals:

private:
  QVBoxLayout*  m_layout;
  QRadioButton* m_prefixMode;
  QLineEdit*    m_prefixEdit;
  QRadioButton* m_replaceMode;
  QLineEdit*    m_oldEdit;
  QLineEdit*    m_newEdit;
};

class ActionsPanel : public QWidget {
  Q_OBJECT
public:
  explicit ActionsPanel(QWidget* parent = nullptr);

signals:

private:
    QVBoxLayout* m_layout;
    QPushButton* m_dest;
    QPushButton* m_preview;
    QPushButton* m_process;
};

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() = default;

  FileSelectionPanel* filePanel() const { return m_filePanel; }

signals:
  void browseRequested();

public slots:
  void setFileList(const QStringList& files);

private:
    NavigationPane*      m_navPane;
    FileSelectionPanel*  m_filePanel;
    ReplaceOptionsPanel* m_replaceOpt;
    ActionsPanel*        m_actions;
    QSplitter*           m_splitter;
};