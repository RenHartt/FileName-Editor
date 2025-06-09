#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class FileModel : public QObject
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = nullptr) : QObject(parent) {}

    void setFiles(const QMap<QString, QString>& files) { m_files = files; }
    const QMap<QString, QString>& files() const { return m_files; }
    void setDstFolder(const QString& path) { m_dstFolder = path; }

    QString dstFolder() const { return m_dstFolder; }

private:
    QMap<QString, QString> m_files;
    QString m_dstFolder;
};