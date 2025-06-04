#pragma once

#include <QObject>
#include <QString>
#include <QPair>
#include <QVector>

class FileModel : public QObject
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = nullptr) : QObject(parent) {}

    using FilePairs = QVector<QPair<QString, QString>>;

    void setFiles(const FilePairs& files) { m_files = files; }
    FilePairs files() const { return m_files; }
    void setDstFolder(const QString& path) { m_dstFolder = path; }

    QString dstFolder() const { return m_dstFolder; }

private:
    FilePairs m_files;
    QString m_dstFolder;
};