#include "include/FileModel.hpp"
#include <QFileInfo>
#include <QDir>
#include <QDebug>

void FileModel::addFile(const QString &filePath, bool selected) {

    qDebug() << "CWD =" << QDir::currentPath();
    qDebug() << "Asked to add:" << filePath;
    qDebug() << "Absolute:" << QFileInfo(filePath).absoluteFilePath();
    qDebug() << "Exists? (QFileInfo):" << QFileInfo(filePath).exists();

    files[filePath] = new QFile(filePath);
    if (selected == true) {
        selectFile(filePath);
    } else {
        deselectFile(filePath);
    }
}

void FileModel::removeFile(const QString &filePath) {
    files.remove(filePath);
}

void FileModel::selectFile(const QString &filePath) {
    files[filePath]->setPermissions(QFile::ReadOwner | QFile::WriteOwner);
}

void FileModel::deselectFile(const QString &filePath) {
    files[filePath]->setPermissions(QFile::ReadOwner);
}

void FileModel::renameFiles(const QString &prefix)
{
    QStringList keys = files.keys();
    int counter = 1;

    for (const QString &origPath : keys) {
        QFile* f = files.value(origPath);
        if (!f->exists())
            continue;

        QString dirPath = QFileInfo(origPath).absoluteDir().absolutePath();
        QString newPath = dirPath + "/" + prefix + QString::number(counter++);

        if (f->rename(newPath)) {
            files.remove(origPath);
            files.insert(newPath, f);
        }
    }

    emit fileListChanged();
}


void FileModel::replaceInFilesName(const QString &oldText, const QString &newText)
{
    QStringList keys = files.keys();

    for (const QString& origPath : keys) {
        if (!origPath.contains(oldText))
            continue;

        QString newPath = origPath;
        newPath.replace(oldText, newText);

        QFile* f = files.value(origPath);
        if (f->exists() && f->rename(newPath)) {
            files.remove(origPath);
            files.insert(newPath, f);
        }
    }

    emit fileListChanged();
}


std::ostream& operator<<(std::ostream& os, const FileModel& model) {
    const auto& files = model.getFiles();
    for (auto it = files.begin(); it != files.end(); ++it) {
        QString path = it.key();
        QFile* file = it.value();
        bool selected = file->permissions().testFlag(QFile::WriteOwner);
        os << (selected ? "[X]" : "[ ]") << path.toStdString() << std::endl;
    }
    return os;
}