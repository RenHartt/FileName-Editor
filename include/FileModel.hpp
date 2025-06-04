#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class FileModel : public QObject
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = nullptr) : QObject(parent) {}

    using FileMap = QMap<QString, QString>;

    void setFiles(const FileMap& files) { m_files = files; }
    FileMap files() const { return m_files; }
    void setDstFolder(const QString& path) { m_dstFolder = path; }

    QString dstFolder() const { return m_dstFolder; }

private:
    FileMap m_files;
    QString m_dstFolder;
};