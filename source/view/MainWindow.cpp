#include "MainWindow.hpp"

NavigationPane::NavigationPane(QWidget* parent)
  : QWidget(parent),
  m_layout(new QVBoxLayout(this)),
  m_fileList(new QListWidget(this)) {
    m_layout->addWidget(m_fileList);
    setLayout(m_layout);
  }

void NavigationPane::setFiles(const QStringList& list) {
  m_fileList->clear();
  m_fileList->addItems(list);
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
		
	  connect(m_browse,&QPushButton::clicked, this, &FileSelectionPanel::browseRequested);
}

ReplaceOptionsPanel::ReplaceOptionsPanel(QWidget* parent)
  : QWidget(parent),
  m_layout(new QVBoxLayout(this)),
  m_prefixMode(new QRadioButton(tr("Prefix"), this)),
  m_prefixEdit(new QLineEdit(this)),
  m_replaceMode(new QRadioButton(tr("Replace"), this)),
  m_oldEdit(new QLineEdit(this)),
  m_newEdit(new QLineEdit(this)) {
    
    auto* buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_prefixMode);
    buttonGroup->addButton(m_replaceMode);
    m_layout->addWidget(m_prefixMode);
    m_layout->addWidget(m_prefixEdit);
    m_layout->addWidget(m_replaceMode);
    m_layout->addWidget(new QLabel(tr("Old:"), this));
    m_layout->addWidget(m_oldEdit);
    m_layout->addWidget(new QLabel(tr("New:"), this));
    m_layout->addWidget(m_newEdit);
    setLayout(m_layout);
}

ActionsPanel::ActionsPanel(QWidget* parent)
  : QWidget(parent),
  m_layout(new QVBoxLayout(this)),
  m_dest(new QPushButton(tr("Destination…"), this)),
  m_preview(new QPushButton(tr("Preview"), this)),
  m_process(new QPushButton(tr("Process"), this)) {
      
	  m_layout->addWidget(m_dest);
	  m_layout->addWidget(m_preview);
	  m_layout->addWidget(m_process);
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

    connect(m_filePanel, &FileSelectionPanel::browseRequested, this, &MainWindow::browseRequested);
}

void MainWindow::setFileList(const QStringList& files) {
  m_navPane->setFiles(files);
}
