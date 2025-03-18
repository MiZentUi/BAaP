#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "date.h"

class FileManager
{
public:
    explicit FileManager();
    explicit FileManager(QString filename);
    void setFilename(QString filename);
    QVector<Date> getDates();
    QVector<QString> getStrings();
    void writeLine(int index, QString string);

private:
    QString filename;
};

#endif //FILEMANAGER_H