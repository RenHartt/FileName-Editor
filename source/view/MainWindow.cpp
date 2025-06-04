#include "MainWindow.hpp"
#include <qboxlayout.h>
#include <qheaderview.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtablewidget.h>
#include <QHeaderView>

NavigationPane::NavigationPane(QWidget* parent)
 : QWidget(parent),
   m_layout(new QVBoxLayout(this)),
   m_table(new QTableWidget(this)) {

  m_table->setColumnCount(2);
  m_table->setHorizontalHeaderLabels({ tr("Source"), tr("Preview") });
  m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->setEditTriggers(QAbstractItemView::DoubleClicked);
  m_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_layout->addWidget(m_table, 1);
  m_layout->setStretch(0, 1);
  setLayout(m_layout);

  connect(m_table, &QTableWidget::cellChanged,
        this, &NavigationPane::cellChanged);
}

void NavigationPane::setEntries(const QMap<QString, QString>& files) {
  int n = files.size();
  m_table->clearContents();
  m_table->setRowCount(n);
  int row = 0;
  for (auto it = files.constBegin(); it != files.constEnd(); ++it, ++row) {
    m_table->setItem(row, 0, new QTableWidgetItem(it.key()));
    m_table->setItem(row, 1, new QTableWidgetItem(it.value()));
  }
}

FileSelectionPanel::FileSelectionPanel(QWidget* parent)
  : QWidget(parent),
  m_buttonLayout(new QHBoxLayout(this)),
  m_browse(new QPushButton(tr("Browse…"), this)),
  m_selectAll(new QPushButton(tr("Select All"), this)),
  m_deselectAll(new QPushButton(tr("Deselect All"), this)) {
  
	  m_buttonLayout->addWidget(m_browse);
	  m_buttonLayout->addWidget(m_selectAll);
	  m_buttonLayout->addWidget(m_deselectAll);
	  setLayout(m_buttonLayout);
}

ReplaceOptionsPanel::ReplaceOptionsPanel(QWidget* parent)
  : QWidget(parent),
  m_layout(new QVBoxLayout(this)),
  m_prefixMode(new QRadioButton(tr("Prefix + index"), this)),
  m_prefixEdit(new QLineEdit(this)),
  m_replaceMode(new QRadioButton(tr("Replace"), this)),
  m_oldEdit(new QLineEdit(this)),
  m_newEdit(new QLineEdit(this)) {
    
    auto* buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_prefixMode);
    buttonGroup->addButton(m_replaceMode);
    m_layout->addWidget(m_prefixMode);
    m_prefixEdit->setPlaceholderText(tr("Prefix"));
    m_layout->addWidget(m_prefixEdit);
    m_layout->addWidget(m_replaceMode);
    m_oldEdit->setPlaceholderText(tr("Old"));
    m_layout->addWidget(m_oldEdit);
    m_newEdit->setPlaceholderText(tr("New"));
    m_layout->addWidget(m_newEdit);
    setLayout(m_layout);
}

ActionsPanel::ActionsPanel(QWidget* parent)
  : QWidget(parent),
  m_layout(new QVBoxLayout(this)),
  m_destEdit(new QLineEdit(this)),
  m_dest(new QPushButton(tr("…"), this)),
  m_preview(new QPushButton(tr("Preview"), this)),
  m_process(new QPushButton(tr("Process"), this)) {
      
    auto* destLayout = new QHBoxLayout;
    m_destEdit->setReadOnly(true);
    m_destEdit->setPlaceholderText(tr("Select dest folder"));
    destLayout->addWidget(m_destEdit, 0);
    m_dest->setFixedSize(40, 30);
    destLayout->addWidget(m_dest, 1);

    auto* actionLayout = new QHBoxLayout;
    actionLayout->addWidget(m_preview);
    actionLayout->addWidget(m_process);

	  m_layout->addLayout(destLayout, 0);
	  m_layout->addLayout(actionLayout, 0);
	
    setLayout(m_layout);
}

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
  m_navPane(new NavigationPane(this)),
  m_filePanel(new FileSelectionPanel(this)),
  m_replaceOpt(new ReplaceOptionsPanel(this)),
  m_actions(new ActionsPanel(this)), 
  m_splitter(new QSplitter(this)) {

    auto* leftWidget = new QWidget(this);
    auto* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(m_navPane);
    leftLayout->addWidget(m_filePanel);
    auto* rightWidget = new QWidget(this);
    auto* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(m_replaceOpt);
    rightLayout->addWidget(m_actions);
    m_splitter->setStretchFactor(0, 1);
    m_splitter->setStretchFactor(1, 2);
    m_splitter->addWidget(leftWidget);
    m_splitter->addWidget(rightWidget);
    setCentralWidget(m_splitter);

    connect(m_filePanel->browseButton(), &QPushButton::clicked,
            this, &MainWindow::browseRequested);
    connect(m_actions->destButton(), &QPushButton::clicked,
            this, &MainWindow::destRequested);
    connect(m_actions->previewButton(), &QPushButton::clicked,
            this, &MainWindow::previewRequested);
    connect(m_actions->processButton(), &QPushButton::clicked,
            this, &MainWindow::processRequested);
    connect(m_navPane, &NavigationPane::cellChanged,
            this, &MainWindow::cellChanged);

}

void MainWindow::setFileList(const QMap<QString, QString>& files) {
  m_navPane->setEntries(files);
}
