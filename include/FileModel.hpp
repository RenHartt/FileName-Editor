#pragma once

#include <QObject>
#include <QString>

class FileModel : public QObject
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = nullptr) : QObject(parent) {}

    void setSrcs(const QStringList& files) { m_srcs = files; }
    void setDsts(const QStringList& files) { m_dsts = files; }
    void setDstFolder(const QString& path) { m_dstFolder = path; }

    QStringList srcs() const { return m_srcs; }
    QStringList dsts() const { return m_dsts; }
    QString dstFolder() const { return m_dstFolder; }

private:
    QStringList m_srcs;
    QStringList m_dsts;
    QString m_dstFolder;
};