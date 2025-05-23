#pragma once

#include <QObject>
#include "FileModel.hpp"

class FileRenamerController : public QObject
{
    Q_OBJECT

public:
    explicit FileRenamerController(FileModel* model, QObject* parent = nullptr);
    FileModel* model() { return m_model; }
    QMap<QString, QFile*> getFiles() const { return m_model->getFiles(); }
public slots:
    void addFile(const QString& path, bool selected = false);
    void removeFile(const QString& path);
    void selectFile(const QString& path);
    void deselectFile(const QString& path);
    void renameSelected(const QString& prefix);
    void replaceSelected(const QString& oldText, const QString& newText);

signals:
    void fileListChanged();

private:
    FileModel* m_model;
};