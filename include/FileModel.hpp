#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <QFile>
#include <ostream>
#include <iostream>

class FileModel : public QObject
{
    Q_OBJECT

public:
    explicit FileModel(QObject *parent = nullptr) : QObject(parent) {}

    QMap<QString, QFile*> getFiles() const { return files; }
    
    void addFile(const QString &file, bool selected = false);
    void removeFile(const QString &file);
    
    void selectFile(const QString &file);
    void deselectFile(const QString &file);
    
    void renameFiles(const QString &prefix);
    void replaceInFilesName(const QString &oldText, const QString &newText);

signals:
    void fileListChanged();

private:
    QMap<QString, QFile*> files;
};

std::ostream& operator<<(std::ostream& os, const FileModel& model);