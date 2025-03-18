#include "filemanager.h"

FileManager::FileManager() {};

FileManager::FileManager(std::string filename)
{
    this->filename = filename;
};

std::string FileManager::getFilename()
{
    return filename;
}

void FileManager::setFilename(std::string filename)
{
    this->filename = filename;
}

bool FileManager::getTrainRoutes(TrainRoute **&trainRoutes, int &size)
{
    std::fstream file(filename, std::ios::in);
    if (file.good())
    {
        size = 0;
        std::string line;
        while (std::getline(file, line))
            size++;
        size /= TrainRoute::FIELDS_COUNT;
        file.clear();
        file.seekg(0, file.beg);
        trainRoutes = new TrainRoute *[size];
        for (int i = 0; i < size; i++)
        {
            trainRoutes[i] = new TrainRoute();
            for (int j = 0; j < TrainRoute::FIELDS_COUNT; j++)
            {
                std::getline(file, line);
                (*trainRoutes[i])[j] = QString::fromStdString(line).replace("\n", "").toStdString();
            }
        }
        file.close();
        return true;
    }
    return false;
}

bool FileManager::save(TrainRoute **trainRoutes, int size)
{
    std::fstream file(filename, std::ios::out);
    if (file.good())
    {
        for (int i = 0; i < size; i++)
            for(int j = 0; j < TrainRoute::FIELDS_COUNT; j++)
                file << (*trainRoutes[i])[j] << std::endl;
        return true;
    }
    return false;
}

#include <QDebug>

bool FileManager::save(std::string filename, TrainRoute **trainRoutes, int size)
{
    std::fstream file(filename, std::ios::out);
    if (file.good())
    {
        for (int i = 0; i< size; i++)
            qDebug() << trainRoutes[i];
        for (int i = 0; i < size; i++)
            for(int j = 0; j < TrainRoute::FIELDS_COUNT; j++)
                file << (*trainRoutes[i])[j] << std::endl;
        return true;
    }
    return false;
}