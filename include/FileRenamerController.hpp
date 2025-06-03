#pragma once

#include <QObject>
#include "FileModel.hpp"
#include "MainWindow.hpp"

class FileRenamerController : public QObject {
    Q_OBJECT
public:
    explicit FileRenamerController(QObject* parent = nullptr);
    void showMainWindow();

signals:
    void filesUpdated(const QStringList& files);

private slots:
    void oncellChanged(int row, int column);

    void onBrowseRequested();

    void onDestRequested();
    void onPreviewRequested();
    void onProcessRequested();

private:
    FileModel*  m_model;
    MainWindow* m_view;
};