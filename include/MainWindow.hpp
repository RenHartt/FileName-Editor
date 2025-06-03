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
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtmetamacros.h>
#include <QFileDialog>
#include <QTableWidget>

enum Mode {
  PrefixMode,
  ReplaceMode
};

class NavigationPane : public QWidget {
    Q_OBJECT
public:
    explicit NavigationPane(QWidget* parent = nullptr);

public slots:
    void setEntries(const QStringList& srcs, const QStringList& dsts);

private:
    QVBoxLayout* m_layout;
    QTableWidget* m_table;
};

class FileSelectionPanel : public QWidget {
    Q_OBJECT
public:
    explicit FileSelectionPanel(QWidget* parent = nullptr);

    QPushButton* browseButton() { return m_browse; }

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

  QRadioButton* prefixMode() { return m_prefixMode; }
  QRadioButton* replaceMode() { return m_replaceMode; }
  QLineEdit* prefixEdit() { return m_prefixEdit; }
  QLineEdit* oldEdit() { return m_oldEdit; }
  QLineEdit* newEdit() { return m_newEdit; }

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

  QPushButton* destButton() { return m_dest; }
  QPushButton* previewButton() { return m_preview; }
  QPushButton* processButton() { return m_process; }
  QLineEdit* destEdit() { return m_destEdit; }

signals:

private:
    QVBoxLayout* m_layout;
    QLineEdit*   m_destEdit;
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

  Mode mode() { return (m_replaceOpt->prefixMode()->isChecked() == true ? PrefixMode : ReplaceMode); }
  QLineEdit* prefix() { return m_replaceOpt->prefixEdit(); }
  QLineEdit* oldEdit() { return m_replaceOpt->oldEdit(); }
  QLineEdit* newEdit() { return m_replaceOpt->newEdit(); }
  QLineEdit* destEdit() { return m_actions->destEdit(); }

signals:
  void browseRequested();

  void destRequested();
  void previewRequested();
  void processRequested();

public slots:
  void setFileList(const QStringList& srcs, const QStringList& dsts);

private:
    NavigationPane*      m_navPane;
    FileSelectionPanel*  m_filePanel;
    ReplaceOptionsPanel* m_replaceOpt;
    ActionsPanel*        m_actions;
    QSplitter*           m_splitter;
};