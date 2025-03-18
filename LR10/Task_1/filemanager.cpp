#include "filemanager.h"

#include <fstream>
#include <sstream>

FileManager::FileManager()
{
    filename = "";
}

FileManager::FileManager(QString filename)
{
    this->filename = filename;
}

void FileManager::setFilename(QString filename)
{
    this->filename = filename;
}

QVector<Date> FileManager::getDates()
{
    QVector<Date> dates;
    if (filename.isEmpty())
        return dates;
    try
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        while (!in.atEnd())
        {
            try
            {
                Date date(in.readLine().trimmed().remove("\n"));
                dates.append(date);
            }
            catch(const std::exception& e)
            {
                dates.append(Date());
            }
        }
    }
    catch(const std::exception& e)
    {
        return QVector<Date>();
    }
    return dates;
}

QVector<QString> FileManager::getStrings()
{
    QVector<QString> strings;
    if (filename.isEmpty())
        return strings;
    try
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString a = in.readLine().trimmed().remove("\n");
            strings.append(a);
        }
    }
    catch(const std::exception& e)
    {
        return QVector<QString>();
    }
    return strings;
}

void FileManager::writeLine(int index, QString string)
{
    std::fstream file;
    file.open(filename.toStdString(), std::ios::in | std::ios::out);
    if (file.good())
    {
        int size = 0;
        std::string line;
        while (std::getline(file, line))
            size++;
        file.clear();
        file.seekg(0, file.beg);
        if (0 <= index && index < size)
        {
            std::stringstream line;
            line << std::setw(10) << std::setfill(' ') << std::left << string.toStdString() << std::endl;
            file.seekp(index * line.str().size(), file.beg);
            file.write(line.str().c_str(), line.str().size());
        }
        else
        {
            std::fstream file;
            file.open(filename.toStdString(), std::ios::app);
            std::stringstream line;
            line << std::setw(10) << std::setfill(' ') << std::left << string.toStdString() << std::endl;
            file << line.str();
        }
        file.close();
    }
}